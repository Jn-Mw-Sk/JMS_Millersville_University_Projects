// File: mufs.c
// Author: Chad Hogg
// Implementation details of the Millersville University File System.
// Part of munix lab in CSCI380.

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "mufs.h"

#define NOT_OPENED -1

// The real file descriptor for the file on which our virtual filesystem is stored.
int FILESYSTEM_FD = NOT_OPENED;

void
setup (const char* diskName)
{
    assert (FILESYSTEM_FD == NOT_OPENED);
    FILESYSTEM_FD = open (diskName, O_RDWR);
    if (FILESYSTEM_FD == NOT_OPENED)
    {
        fprintf (stderr, "Could not open file %s: %s\n", diskName, strerror (errno));
        exit (EXIT_FAILURE);
    }
    char first8[8];
    if (read (FILESYSTEM_FD, first8, sizeof (first8)) < sizeof (first8))
    {
        fprintf (stderr, "Could not read filesystem identifier from %s: %s\n", diskName, strerror (errno));
        exit (EXIT_SUCCESS);
    }
    assert (strcmp (first8, VERSION10) == 0);
}

void
teardown ()
{
    assert (FILESYSTEM_FD != NOT_OPENED);
    int result = close (FILESYSTEM_FD);
    if (result != 0)
    {
        fprintf (stderr, "Could not teardown filesystem: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
    FILESYSTEM_FD = NOT_OPENED;
}

void
sanityCheck ()
{
    assert (sizeof (struct superBlock) == BLOCK_SIZE);
    assert (sizeof (struct freeBlockMap) == BLOCK_SIZE);
    assert (sizeof (struct iNode) == INODE_SIZE);
    assert (sizeof (struct dirEntry) == DIR_ENTRY_LENGTH);
    assert (FIRSTDATABLOCK_NUMBER == FIRSTINODEBLOCK_NUMBER + INODE_COUNT * INODE_SIZE / BLOCK_SIZE);
}

void
verifyINode (struct iNode* buffer)
{
    uint16_t type = buffer->mode & (MU_S_AVAIL | MU_S_DIREC | MU_S_REGLR);
    assert (type == MU_S_AVAIL || type == MU_S_DIREC || type == MU_S_REGLR);
}

void
verifyFreeBlockMap (struct freeBlockMap* buffer)
{
    for (int blockNum = 0; blockNum < BLOCK_COUNT; ++blockNum)
    {
        assert (buffer->isUsed[blockNum] == BLOCK_USED || buffer->isUsed[blockNum] == BLOCK_AVAILABLE);
        assert (blockNum >= FIRSTDATABLOCK_NUMBER || buffer->isUsed[blockNum] == BLOCK_USED);
    }
}

void
readINode (uint32_t iNodeNumber, struct iNode* buffer)
{
    assert (FILESYSTEM_FD != NOT_OPENED);
    assert (iNodeNumber < INODE_COUNT);
    int offset = FIRSTINODEBLOCK_NUMBER * BLOCK_SIZE + iNodeNumber * INODE_SIZE;
    int result = lseek (FILESYSTEM_FD, offset, SEEK_SET);
    if (result < 0)
    {
        fprintf (stderr, "Could not seek to inode %d on disk: %s\n", iNodeNumber, strerror (errno));
        exit (EXIT_FAILURE);
    }
    int bytes = read (FILESYSTEM_FD, buffer, INODE_SIZE);
    if (bytes < INODE_SIZE)
    {
        fprintf (stderr, "Failed to read inode %d from disk: %s\n", iNodeNumber, strerror (errno));
        exit (EXIT_FAILURE);
    }
    verifyINode (buffer);
}

void
writeINode (uint32_t iNodeNumber, struct iNode* buffer)
{
    verifyINode (buffer);
    assert (FILESYSTEM_FD != NOT_OPENED);
    assert (iNodeNumber < INODE_COUNT);
    int offset = FIRSTINODEBLOCK_NUMBER * BLOCK_SIZE + iNodeNumber * INODE_SIZE;
    int result = lseek (FILESYSTEM_FD, offset, SEEK_SET);
    if (result < 0)
    {
        fprintf (stderr, "Could not seek to inode %d on disk: %s\n", iNodeNumber, strerror (errno));
        exit (EXIT_FAILURE);
    }
    int bytes = write (FILESYSTEM_FD, buffer, INODE_SIZE);
    if (bytes < INODE_SIZE)
    {
        fprintf (stderr, "Failed to write inode %d from disk: %s\n", iNodeNumber, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

void
readFreeBlockMap (struct freeBlockMap* buffer)
{
    assert (FILESYSTEM_FD != NOT_OPENED);
    int offset = FREEBLOCKMAP_NUMBER * BLOCK_SIZE;
    int result = lseek (FILESYSTEM_FD, offset, SEEK_SET);
    if (result < 0)
    {
        fprintf (stderr, "Could not seek to free block map on disk: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
    int bytes = read (FILESYSTEM_FD, buffer, BLOCK_COUNT);
    if (bytes < BLOCK_COUNT)
    {
        fprintf (stderr, "Failed to read free block map from disk: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
    verifyFreeBlockMap (buffer);
}

void
writeFreeBlockMap (struct freeBlockMap* buffer)
{
    verifyFreeBlockMap (buffer);
    assert (FILESYSTEM_FD != NOT_OPENED);
    int offset = FREEBLOCKMAP_NUMBER;
    int result = lseek (FILESYSTEM_FD, offset, SEEK_SET);
    if (result < 0)
    {
        fprintf (stderr, "Could not seek to free block map on disk: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
    int bytes = write (FILESYSTEM_FD, buffer, BLOCK_COUNT);
    if (bytes < BLOCK_COUNT)
    {
        fprintf (stderr, "Failed to write block map to disk: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
}

void
readDataBlock (uint32_t blockNum, char buffer[BLOCK_SIZE])
{
    assert (FILESYSTEM_FD != NOT_OPENED);
    assert (blockNum >= FIRSTDATABLOCK_NUMBER && blockNum < BLOCK_COUNT);
    int offset = blockNum * BLOCK_SIZE;
    int result = lseek (FILESYSTEM_FD, offset, SEEK_SET);
    if (result < 0)
    {
        fprintf (stderr, "Could not seek to data block %d on disk: %s\n", blockNum, strerror (errno));
        exit (EXIT_FAILURE);
    }
    int bytes = read (FILESYSTEM_FD, buffer, BLOCK_SIZE);
    if (bytes < BLOCK_SIZE)
    {
        fprintf (stderr, "Failed to read data block %d from disk: %s\n", blockNum, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

void
writeDataBlock (uint32_t blockNum, char buffer[BLOCK_SIZE])
{
    assert (FILESYSTEM_FD != NOT_OPENED);
    assert (blockNum >= FIRSTDATABLOCK_NUMBER && blockNum < BLOCK_COUNT);
    int offset = blockNum * BLOCK_SIZE;
    int result = lseek (FILESYSTEM_FD, offset, SEEK_SET);
    if (result < 0)
    {
        fprintf (stderr, "Could not seek to data block %d on disk: %s\n", blockNum, strerror (errno));
        exit (EXIT_FAILURE);
    }
    int bytes = write (FILESYSTEM_FD, buffer, BLOCK_SIZE);
    if (bytes < BLOCK_SIZE)
    {
        fprintf (stderr, "Failed to write data block %d to disk: %s\n", blockNum, strerror (errno));
        exit (EXIT_FAILURE);
    }
}
