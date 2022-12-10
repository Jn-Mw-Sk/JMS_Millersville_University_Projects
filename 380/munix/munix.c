// File: munix.c
// Author: Chad Hogg & Matt Shenk
// Implementation of Munix file-related system calls.
// Part of munix lab in CSCI380.

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "munix.h"
#include "mufs.h"
#include "muusers.h"
#include "muerrno.h"


//// Types that are only relevant to this file //////////


// All the information about a file that a process has open.
// In real UNIX that would be split across three different structures.
struct openFile
{
    // The inode of the file.
    struct iNode inode;
    // The block (if any) that is currently buffered.
    char currentData[BLOCK_SIZE];
    // The index (into the inode's direct blocks array) of which block is currently
    //   buffered, or -1 if none are buffered.
    uint32_t currentBlockIndex;
    // The location in the file where the next byte would be read / written.
    uint32_t filePointer;
    // The flags used when this file was opened.
    int flags;
    // Whether or not the buffered block (if any) has been modified.
    int dirty;
    // The number of this file's inode, or -1 to indicate no open file.
    int iNodeNumber;
};


//// Constants that are only relevant to this file /////////////

#define FILE_TABLE_SIZE 10


//// Global variables //////////////////////////////////////////


// The table of files that the process has open.
// Indexes into this array are used as file descriptors.
struct openFile files[FILE_TABLE_SIZE];

// The user number of the currently-logged in user.
int activeUserNumber;

// The group number of the currently-logged in group.
int activeGroupNumber;

// The inode of the processe's current working directory.
struct iNode workingDirINode;


//// Helper functions //////////////////////////////////////////


// Finds a file in a directory.
// Params:
//   name - The name of the file we are searching for.
//   dirNode - The inode of the directory in which we are searching.
// Returns:
//   The inode number of the file, or -1 if the file does not exist.
int
findFile (const char* name, const struct iNode* dirNode)
{
    //TODO
    char * file[1024];
    for(int x = 0; x < 12; x++){
        readDataBlock(dirNode->directBlocks[x], file);
        if(strcmp(file->dirEntry.name, name) == 0)
        {
            return x;
        }
    }
    
    return -1;
}

// Determines whether or not the process can read a file.
// Params:
//   node The inode of the file.
// Returns:
//   1 if the process has read permission, 0 otherwise.
int
canRead (const struct iNode* node)
{
    if(node->userOwner = activeUserNumber)
        return 1;
    else if(node->groupOwner = activeGroupNumber)
        return 1;

    return 0;
}

// Determines whether or not the process can write a file.
// Params:
//   node The inode of the file.
// Returns:
//   1 if the process has write permission, 0 otherwise.
int
canWrite (const struct iNode* node)
{
    if(node->userOwner = activeUserNumber)
        return 1;
    else if(node->groupOwner = activeGroupNumber)
        return 1;

    return 0;

    return 0;
}

// Determines whether or not the process can execute a file.
// Params:
//   node The inode of the file.
// Returns:
//   1 if the process has execute permission, 0 otherwise.
int canExecute (const struct iNode* node)
{
    if(node->userOwner = activeUserNumber)
        return 1;
    else if(node->groupOwner = activeGroupNumber)
        return 1;

    return 0;
}

// Searches for a free block, marking it as used.
// Returns:
//   The number of the previously-free block if one is found, or -1 if none are found.
int
findAndMarkFreeBlock ()
{
    // TODO
    struct freeBlockMap buffer[BLOCK_SIZE];
    readDataBlock(buffer);
    return -1;
}

//// Library functions /////////////////////////////////////////

int
muinit (const char* userName, const char* groupName)
{
    // TODO

    // Look up user and group numbers, check for existence and membership.
    if(lookUpUserNumber(userName) == -1){
        muerrno = MU_E_NO_SUCH_USER;
        return -1;
    }
    if(lookUpGroupNumber(groupName) == -1){
        muerrno = MU_E_NO_SUCH_GROUP;
        return -1;
    }
    if(isUserInGroup(lookUpUserNumber(userName), lookUpGroupNumber(groupName)) == 0){
        muerrno = MU_E_NOT_MEMBER;
        return -1;
    }
    // Set user and group number.
    activeUserNumber = lookUpUserNumber(userName);
    activeGroupNumber = lookUpGroupNumber(groupName);
    
    // Set each file table entry to be for inode number -1.
    for(int x = 0; i < FILE_TABLE_SIZE; i++){
        files[x].iNodeNumber = -1;
    }

    workingDirInode = files[0].inode;

    return 0;
}

int
mucd (const char* dirName)
{
    // TODO

    // Check for valid directory name.
    if(dirName.strstr("/") == NULL || strcmp(dirName, "") == 0){
        muerrno = MU_E_BAD_NAME;
        return 0;
    }
    // Find iNode associated with name / check that it exists.
    bool found = false;
    char * file[1024];
    int nodeNum;
    for(int x = 0; x < 12; x++){
        readDataBlock(dirNode->directBlocks[x], file);
        if(strcmp(file->dirEntry.name, dirName) == 0)
        {
            nodeNum = x;
            found = true;
        }
    }
    if(found == false){
        muerrno = MU_E_DOES_NOT_EXIST;
        return 0;
    }
    
    // Read inode associated with directory.
    struct iNode nodeBuffer[INODE_SIZE];
    readInode(nodeNum, &nodeBuffer);

    // Check that file type is directory.
    
 
    // Check that directory can be executed.
    if(canRead(nodeBuffer) == 0){
        muerrno = MU_E_PERMISSION;
        return 0;
    }

    // Overwrite working directory inode with this directory's inode.
    workingDirINode = dirINode;

    return 0;
}

int
muopen (const char* fileName, int flags)
{
    // TODO
    int fileSpot = -1;
    // Find an unused location in the file descriptor table.
    for(int x = 0; x < FILE_TABLE_SIZE; i++)
    {
        if(openFile[x] == -1)
        {
            fileSpot = x;
            break;
        }
    }

    // Check for existence of unused location in file descriptor table.
    if(fileSpot < 0){
        muerrno = MU_E_FULL_TABLE;
        return;
    }

    // Check for valid file name.
    if(fileName.strstr("/") == NULL || strcmp(fileName, "") == 0){
        muerrno = MU_E_BAD_NAME;
        return -1;
    }

    // Find inode associated with name / check that it exists.
    
 

    // Read file's inode.

    // Check that file type is regular file.

    // Check for read permission if we are requesting it.
    if(canRead())
    // Check for write permission if we are requesting it.

    // Copy iNode into chosen spot in file descriptor table, set it up for appropriate
    //   permissions with no data block loaded and file pointer at 0.

    return -1;
}

int
muclose (int fd)
{
    // TODO
    bool found = false;
    int nodeIndex = 0;
    // Check for valid file descriptor.
    for(int x = 0; x < FILE_TABLE_SIZE; x++){
        if(fd == x){
            break;
        }
    }
    if(found == false){
        muerrno = MU_E_INVALID_FD;
        return -1;
    }

    // Write block to disk if dirty.
    char buff[BLOCK_SIZE];
    writeDataBlock(fd, buff);

    // Mark location's inode as available.
    openFile[nodeIndex = -1;]

    return 0;
}

int
muread (int fd, char* buffer, int n)
{
    // TODO
    // Check for valid file descriptor.
    bool found = false;
    for(int x = 0; x < FILE_TABLE_SIZE; x++){
        if(fd == openFile[x]){
            found == true;
            break;
        }
    }
    if(found == false){
        muerrno = MU_E_INVALID_FD;
        return -1;
    }

    // Check that file is open for reading.

    // Read until n bytes have been read or end of file reached.

    while (0 /*something*/)
    {
        // If wrong block loaded, unload it and write if dirty.

        // If no block loaded, load it.

        // Copy one byte.

    }

    return -1;
}

int
muwrite (int fd, const char* buffer, int n)
{
    // TODO

    // Check for valid file descriptor.

    // Check that file is open for writing.

    // Write until n bytes have been written or file is maximum length.
    int readIn
    while (0 /*something*/)
    {
        // If wrong block loaded, unload it and write if dirty.

        // If no block loaded, load it.
        if (0 /*something*/)
        {
            // If block does not yet exist, allocate one for it.

            // Load the block
        }
        // Copy one byte, increasing size if necessary.

    }
    // Write inode in case file size / direct blocks changed.

    return -1;
}

void
muls ()
{
    // TODO
    for(int x = 0; x < FILE_TABLE_SIZE; x++){
        
    }

}