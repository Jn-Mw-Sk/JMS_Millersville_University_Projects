/**
 * @file fs.c
 * @author John "Matt" Shenk
 * @brief A program to simulate a filesystem that only holds 16 files
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 * In my implementation of this filesystem lab I tried to follow along with the 
 *       pseudocode, with mixed results. Probably the hardest method was create.
 *       Once I had that (mostly) working it made implementng the other methods 
 *       a lot easier. My fs_repl method, since I've heard it's not really required,
 *       has some hard-coded function calls to test out diffeent methods. (in hindsight
 *       though, I wish I wouldve added a "command" to create a new disk on the fly for 
 *       ease of use). As of writing this, there's a bug where is a bunch of files are created
 *       and multiple are deleted something about allocating the now free blocks gets confused  
 *
 */

#include "fs.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>


#define FS_NUM_BLOCKS    128
#define FS_MAX_FILE_SIZE 8
#define FS_MAX_FILENAME  16
#define FS_MAX_FILES     16
#define FS_BLOCK_SIZE    1024

// I-Node struct
struct iNode
{
  char name[FS_MAX_FILENAME];
  int size;
  int blockPointers[FS_MAX_FILE_SIZE];
  int used;
};

struct fs_t
{
  int fd;
};

// open the file with the above name
void
fs_open (struct fs_t *fs, char diskName[16])
{
  printf("=> Opening disk file...\n");
  // this file will act as the "disk" for your file system
  fs->fd = open(diskName, O_RDWR, 0);
  if(fs->fd < 0)
  {
    perror("Error");
    exit(1);
  }
  return;
}

// close and clean up all associated things
void
fs_close (struct fs_t *fs)
{
  printf("\n=> Closing disk file...\n");
  // this file will act as the "disk" for your file system
  close(fs->fd);
}

// create a file with this name and this size
/*
 * Getting this function to work was probably the hardest part of the lab. (everything else I could build off of
      what's going on in this method).

 */
void
fs_create (struct fs_t *fs, char name[16], int size)
{
  int nodePosition = 128;
  char blockBuffer[128];
  int numFree = 0;
  bool found = false;
  int allocated = 0;
  struct iNode currentINode;

  // high level pseudo code for creating a new file
  // Step 1: check to see if we have sufficient free space on disk by
  // reading in the free block list. To do this:
  // - move the file pointer to the start of the disk file.

  
  if(lseek(fs->fd, 0, 0) < 0){ perror("Error: "); exit(1); }

  // - Read the first 128 bytes (the free/in-use block information)

  if(read(fs->fd, &blockBuffer, 128) < 0){ perror("Error: "); exit(1); }

  // - Scan the list to make sure you have sufficient free blocks to
  //   allocate a new file of this size
  if(size > FS_MAX_FILE_SIZE || size < 1)
  {
    printf("=> File of size %d not allowed.\n", size);
    return;
  } 
  else 
  {
    for(int i = 0; i < 128; i++)
    {
      if(blockBuffer[i] == 0)
        numFree++;
    }
    //printf("%d", numFree);
    if(numFree < size) // Not enough free blocks for the INode
    {
      printf("=> Not enough space on disk (no more free blocks).\n");
      return;
    }
  }

  // Step 2: we look  for a free inode on disk
  // - Read in a inode
  // - check the "used" field to see if it is free
  // - If not, repeat the above two steps until you find a free inode

  // Make sure there is not an iNode with the same name
  for(int i = 0; i < FS_MAX_FILES; ++i){
    if(lseek(fs->fd, 128 + (56 * i), SEEK_SET) < 0){ perror("Error: "); exit(1);}
    if(read(fs->fd, &currentINode, 56) < 0){ perror("Error: "); exit(1);}
    if(strcmp(currentINode.name, name) == 0)
    {
      printf("Filename already exists.");
      return;
    }

  }

  for(int i = 0; i < FS_MAX_FILES; ++i){
    if(lseek(fs->fd, 128 + (56 * i), SEEK_SET) < 0){ perror("Error: "); exit(1);}
    if(read(fs->fd, &currentINode, 56) < 0){ perror("Error: "); exit(1);}
    nodePosition = 128+(56 * i);
      if(currentINode.used == 0)
      {
        // - Set the "used" field to 1
        // - Copy the filename to the "name" field
        // - Copy the file size (in units of blocks) to the "size" field
        currentINode.used = 1;
        strcpy(currentINode.name, name);
        currentINode.size = size;
        found = true;
        break;
      }
  }
  if(found == false) // No INodes found
  {
    printf("\n=> Not enough space on disk.(No more INodes)\n");
    return;
  }

  // Step 3: Allocate data blocks to the file
  // - Scan the block list that you read in Step 1 for a free block
  // - Once you find a free block, mark it as in-use (Set it to 1)
  // - Set the blockPointer[i] field in the inode to this block number.
  // - repeat until you allocated "size" blocks
  for(int i = 1; i < 128; i++)
  {
    
    if(blockBuffer[i] == 0)
    {
      
      for(int j = 0; j < 8; j++)
      {
        if(currentINode.blockPointers[j] == 0)
        {
          blockBuffer[i] = 1;
          currentINode.blockPointers[j] = i;
          printf("%d ", currentINode.blockPointers[j]);
          break;
        }
      }
      
      allocated++;
      if(allocated == size)
        break;
    }

  }

  // Step 4: Write out the inode and free block list to disk
  // - Move the file pointer to the start of the file
  if(lseek(fs->fd, 0, 0) < 0){ perror("Error: "); exit(1);}
  // - Write out the 128 byte free block list
  int writeStat = write(fs->fd, &blockBuffer, 128);
  if(writeStat < 0)
  {
    perror("Error: ");
    return;
  }
  // - Move the file pointer to the position on disk where this inode was stored
  if(lseek(fs->fd, nodePosition, SEEK_SET) < 0){ perror("Error: "); exit(1);}
  // - Write out the inode
  writeStat = write(fs->fd, &currentINode, 56);
  if(writeStat < 0)
  {
    perror("Error: ");
    return;
  }
  printf("\n=> File '%s' with size %d created\n", name, size);
  return;
}

// Delete the file with this name
void
fs_delete (struct fs_t *fs, char name[16])
{
  int nodePosition;
  struct iNode currentINode;
  bool found = false;
  char blockBuffer[128];
  char deleteABlock[1024];

  // Step 1: Locate the inode for this file
  //   - Move the file pointer to the 1st inode (129th byte)
  if(lseek(fs->fd, 129, SEEK_SET ) < 0){
    perror("lseek");
    exit(0);
  }
  //   - Read in a inode
  //   - If the iinode is free, repeat above step.
  //   - If the iinode is in use, check if the "name" field in the
  //     inode matches the file we want to delete. IF not, read the next
  //     inode and repeat
  
  for(int i = 0; i < FS_MAX_FILES; i++){
    if(lseek(fs->fd, 128 + (56 * i), SEEK_SET) < 0){ perror("lseek"); exit(0); }
    if(read(fs->fd, &currentINode, 56) < 0){ perror("read"); exit(0); }
    nodePosition = 128+(56 * i);
    if(currentINode.used == 1)
    {
      if(strcmp(currentINode.name, name) == 0){
        found = true;
        break;
      }
    }
  }
  if(found == false) // File not found
  {
    printf("=> File '%s' not found\n", name);
    return;
  }
  // Step 2: free blocks of the file being deleted
  // Read in the 128 byte free block list (move file pointer to start
  //   of the disk and read in 128 bytes)
  lseek(fs->fd, 0l, SEEK_SET);
  read(fs->fd, &blockBuffer, 128);
  // Free each block listed in the blockPointer fields
  for(int i = 0; i < FS_MAX_FILE_SIZE; i++)
  {
    if(currentINode.blockPointers[i] != 0)
    {
      blockBuffer[currentINode.blockPointers[i]] = 0;
    }
      
  }

  // Step 3: mark inode as free
  // Set the "used" field to 0.
  currentINode.used = 0;

  // Step 4: Write out the inode and free block list to disk
  // - Move the file pointer to the start of the file
  lseek(fs->fd, 0, 0);
  // - Write out the 128 byte free block list
  int writeStat = write(fs->fd, &blockBuffer, 128);
  if(writeStat < 0)
  {
    perror("Write error...");
    return;
  }
  // - Move the file pointer to the position on disk where this inode was stored
  lseek(fs->fd, nodePosition, SEEK_SET);
  // - Write out the inode
  writeStat = write(fs->fd, &currentINode, 56);
  if(writeStat < 0)
  {
    perror("Write error...");
    return;
  }

  printf("\n=> File '%s' deleted, %d block(s) freed\n",name, currentINode.size);

}

// List names of all files on disk
void
fs_ls (struct fs_t *fs)
{
  struct iNode currentINode;
  // Step 1: read in each inode and print!
  // Move file pointer to the position of the 1st inode (129th byte)
  lseek(fs->fd, 128, SEEK_SET);

  // for each inode:
  //   read it in
  //   if the inode is in-use
  //     print the "name" and "size" fields from the inode
  // end for
  for(int i = 1; i <= 16; i++)
  {
    read(fs->fd, &currentINode, 56);
   
    if(currentINode.used == 1)
    {   
        printf("%16s %6dB\n", currentINode.name, currentINode.size);
    }
    lseek(fs->fd, 128 + 56 * i, SEEK_SET);
  }
}

// read this block from this file
void
fs_read (struct fs_t *fs, char name[16], int blockNum, char buf[1024])
{
  struct iNode currentINode;
  bool found = false;

  // Step 1: locate the inode for this file
  //   - Move file pointer to the position of the 1st inode (129th byte)
  lseek(fs->fd, 128, SEEK_SET);

  //   - Read in a inode
  //   - If the inode is in use, compare the "name" field with the above file
  //   - If the file names don't match, repeat
    for(int i = 1; i <= 16; i++)
  {
    read(fs->fd, &currentINode, 56);
   
    if(strcmp(currentINode.name, name) == 0)
    {   
      found = true;
      break;
    }
    lseek(fs->fd, 128 + 56 * i, SEEK_SET);
  }

  if(found == false)
  {
    printf("File %s not found\n", name);
    return;
  }

  // Step 2: Read in the specified block
  // Check that blockNum < inode.size, else flag an error
  if(blockNum >= currentINode.size){
    printf("File does not have this block.\n");
    return;
  }
  // Get the disk address of the specified block
  // move the file pointer to the block location
  if(lseek(fs->fd, 1024 + currentINode.blockPointers[blockNum] * 1024, SEEK_SET) < 0)
  {
    perror("lseek");
    return;
  }

  // Read in the block! => Read in 1024 bytes from this location into the buffer
  // "buf"
  printf("\nReading file %s at block #%d\n", name, blockNum);
  if(read(fs->fd, buf, 1024) < 0)
  {
    perror("read");
  }
  return;
}

// write this block to this file
void
fs_write (struct fs_t *fs, char name[16], int blockNum, char buf[1024])
{
  struct iNode currentINode;
  bool found = false;

  // Step 1: locate the inode for this file
  //   - Move file pointer to the position of the 1st inode (129th byte)
  lseek(fs->fd, 128, SEEK_SET);

  //   - Read in a inode
  //   - If the inode is in use, compare the "name" field with the above file
  //   - If the file names don't match, repeat
    for(int i = 1; i <= 16; i++)
  {
    read(fs->fd, &currentINode, 56);
   
    if(strcmp(currentINode.name, name) == 0)
    {   
      found = true;
      break;
    }
    lseek(fs->fd, 128 + 56 * i, SEEK_SET);
  }

  if(found == false)
  {
    printf("File %s not found", name);
  }
  // Step 2: Write to the specified block
  // Check that blockNum < inode.size, else flag an error
  if(blockNum >= currentINode.size){
    printf("File does not have this block.\n");
    return;
  }
  // Get the disk address of the specified block
  // move the file pointer to the block location
  lseek(fs->fd, 1024 + currentINode.blockPointers[blockNum] * 1024, SEEK_SET);
  
  printf("Writing block #%d to file %s\n", blockNum, name);

  // Write the block! => Write 1024 bytes from the buffer "buf" to this location
  if(write(fs->fd, buf, 1024) < 0){ perror("write"); return; }
}

// REPL entry point
/*
* I just hard-coded some commands for testing
*/
void
fs_repl ()
{
  printf("Welcome\n");
  struct fs_t disk0 = {0};
  char diskName[16];
  strcpy(diskName, "disk0");
  char fileName[16];
  char readBuffer[1024];
  char writeBuffer[1024];

  fs_open(&disk0, diskName);
  strcpy(fileName, "a");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "b");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "c");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "d");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "e");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "f");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "g");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "h");
  fs_create(&disk0, fileName, 1);
  strcpy(fileName, "a");
  fs_delete(&disk0, fileName);
    strcpy(fileName, "c");
  fs_delete(&disk0, fileName);
    strcpy(fileName, "e");
  fs_delete(&disk0, fileName);
    strcpy(fileName, "g");
  fs_delete(&disk0, fileName);
  strcpy(fileName, "i");
  fs_create(&disk0, fileName, 8);


  /*
  strcpy(fileName, "lab.java");
  fs_create(&disk0, fileName, 7);\
  fs_ls(&disk0);

  strcpy(fileName, "lab.java");
  fs_delete(&disk0, fileName);
  fs_ls(&disk0);

  strcpy(fileName, "lab.java");
  fs_delete(&disk0, fileName);


  strcpy(fileName, "file1");
  
  strcpy(writeBuffer, "You have read this block from file1\n");
  fs_write(&disk0, fileName, 2, writeBuffer);
  fs_read(&disk0, fileName, 2, readBuffer);
  printf("%s", readBuffer);

  strcpy(fileName, "file2");
  fs_create(&disk0, fileName, 3);

  strcpy(writeBuffer, "You have read this block from file2\n");
  fs_write(&disk0, fileName, 2, writeBuffer);
  fs_read(&disk0, fileName, 2, readBuffer);
  printf("%s", readBuffer);

  fs_read(&disk0, fileName, 5, readBuffer);
  */
  fs_close(&disk0);

  return;
}


int main(){
  fs_repl();
}





