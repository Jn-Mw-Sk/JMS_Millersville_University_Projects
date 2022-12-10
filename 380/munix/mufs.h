// File: mufs.h
// Author: Chad Hogg
// Public interface of the Millersville University File System.
// Part of munix lab in CSCI380.

#ifndef MUFS_H
#define MUFS_H

#include <stdint.h>

#define VERSION10 "mufs1.0"
#define BLOCK_SIZE 1024
#define BLOCK_COUNT 1024
#define IDENTIFIER_LENGTH 8
#define INODE_SIZE 64
#define INODE_COUNT 256
#define NUM_DIRECT_BLOCKS 12
#define SUPERBLOCK_NUMBER 0
#define FREEBLOCKMAP_NUMBER 1
#define FIRSTINODEBLOCK_NUMBER 2
#define FIRSTDATABLOCK_NUMBER 18
#define MAX_NAME_LENGTH 28
#define DIR_ENTRY_LENGTH 32
#define DIR_ENTRIES_PER_BLOCK (BLOCK_SIZE / DIR_ENTRY_LENGTH)
#define BLOCK_USED 1
#define BLOCK_AVAILABLE 0
#define MAX_FILE_SIZE (NUM_DIRECT_BLOCKS * BLOCK_SIZE)

#define MU_O_RDONLY 1
#define MU_O_WRONLY 2
#define MU_O_RDWR 3

#define MU_S_IXOTH 1    // 00000000 00000001
#define MU_S_IWOTH 2    // 00000000 00000010
#define MU_S_IROTH 4    // 00000000 00000100
#define MU_S_IXGRP 8    // 00000000 00001000
#define MU_S_IWGRP 16   // 00000000 00010000
#define MU_S_IRGRP 32   // 00000000 00100000
#define MU_S_IXUSR 64   // 00000000 01000000
#define MU_S_IWUSR 128  // 00000000 10000000
#define MU_S_IRUSR 256  // 00000001 00000000
#define MU_S_REGLR 512  // 00000010 00000000
#define MU_S_DIREC 1024 // 00000100 00000000
#define MU_S_AVAIL 2048 // 00001000 00000000
#define MU_S_IRWXO 7    // 00000000 00000111
#define MU_S_IRWXG 56   // 00000000 00111000
#define MU_S_IRWXU 448  // 00000001 11000000

// The structure of the filesystem superblock.
struct superBlock
{
    // An 8-character identifier -- should be VERSION10.
    char identifier[IDENTIFIER_LENGTH];
    // Space reserved for use in later versions of the filesystem.
    char reserved[BLOCK_SIZE - IDENTIFIER_LENGTH];
};

// The structure of the free block map.
struct freeBlockMap
{
    // A byte per block that contains either 1 for used or 0 for available.
    char isUsed[BLOCK_SIZE];
};

// The structure of an inode.
struct iNode
{
    // The ID number of the user who owns the file.
    uint16_t userOwner;
    // The ID number of the group who owns the file.
    uint16_t groupOwner;
    // The file mode (more details elsewhere).
    uint32_t mode;
    // The file size, in bytes.
    uint32_t size;
    // The number of hard links to the file.
    uint32_t linkCount;
    // The numbers of the first 10 data blocks.
    uint32_t directBlocks[NUM_DIRECT_BLOCKS];
};

// An entry in a directory.
struct dirEntry
{
    // The number of the inode used by this entry.
    uint32_t iNodeNumber;
    // The name of this entry.
    char name[MAX_NAME_LENGTH];
};

// The real file descriptor for the file on which our virtual filesystem is stored.
extern int FILESYSTEM_FD;



// Loads an MUFS filesystem so that you can interact with it.
void
setup (const char* diskName);


// Unloads an MUFS filesystem when you are finished with it.
void
teardown ();


// A function that ensures all of our math is correct.
void
sanityCheck ();


// Checks that an inode contains sensible values.
void
verifyINode (struct iNode* buffer);


// Checks that a free block map contains sensible values.
void
verifyFreeBlockMap (struct freeBlockMap* buffer);


// Reads the contents of an inode from disk into memory.
void
readINode (uint32_t iNodeNumber, struct iNode* buffer);


// Write the contents of an inode from memory onto the disk.
void
writeINode (uint32_t iNodeNumber, struct iNode* buffer);


// Reads the free block map from disk.
void
readFreeBlockMap (struct freeBlockMap* buffer);


// Writes the free block map to disk.
void
writeFreeBlockMap (struct freeBlockMap* buffer);


// Reads a data block from disk.
void
readDataBlock (uint32_t blockNum, char buffer[BLOCK_SIZE]);


// Writes a data block to disk.
void
writeDataBlock (uint32_t blockNum, char buffer[BLOCK_SIZE]);

#endif//MUFS_H