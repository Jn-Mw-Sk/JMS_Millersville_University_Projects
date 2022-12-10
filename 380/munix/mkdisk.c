// File: mkdisk.c
// Author: Chad Hogg
// A program that generates an example MUFS disk file.
// Part of CSCI380 munix lab.

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "mufs.h"
#include "muusers.h"

#define DEFAULT_DISK_NAME "disk0.dat"

struct entireFileSystem
{
    char superblock[BLOCK_SIZE];
    char freeBlockMap[BLOCK_SIZE];
    struct iNode iNodes[INODE_COUNT];
    char dataBlocks[BLOCK_COUNT - FIRSTDATABLOCK_NUMBER][BLOCK_SIZE];
};

void
format (struct entireFileSystem* fs);

void
createDirectory (struct entireFileSystem* fs, int parentINodeNum, char* name, int userId, int groupId, int mode);

int
findAvailableINode (struct entireFileSystem* fs);

int
findAvailableDataBlock (struct entireFileSystem* fs);

void
createLink (struct entireFileSystem* fs, int dirINode, int contentINode, const char* name);

int
findINode (struct entireFileSystem* fs, int currentINodeNumber, const char* name);

void
createFile (struct entireFileSystem* fs, int parentINodeNum, char* name, int userId, int groupId, int mode, char* text, int size);

int
main (int argc, char* argv[])
{
    char* diskName = DEFAULT_DISK_NAME;
    if (argc == 2)
    {
        diskName = argv[1];
    }

    struct entireFileSystem fs;
    format (&fs);

    createDirectory (&fs, 0, "java", lookUpUserNumber ("hogg"), lookUpGroupNumber ("162"), MU_S_DIREC | MU_S_IRWXU | MU_S_IRGRP | MU_S_IXGRP);
    createFile (&fs, 1, "foo.txt", lookUpUserNumber ("hogg"), lookUpGroupNumber ("162"), MU_S_IRUSR | MU_S_IWUSR | MU_S_IRGRP, "abcde", 2074);
    createFile (&fs, 1, "bar.java", lookUpUserNumber ("cain"), lookUpGroupNumber ("162"), S_IRUSR | S_IWUSR | S_IRGRP, "qwer", 513);

    createDirectory (&fs, 0, "c++", lookUpUserNumber ("zoppetti"), lookUpGroupNumber ("362"), MU_S_DIREC | MU_S_IRUSR | MU_S_IWUSR | MU_S_IXUSR | MU_S_IRGRP | MU_S_IXGRP | MU_S_IXGRP);
    createDirectory (&fs, 4, "labs", lookUpUserNumber ("zoppetti"), lookUpGroupNumber ("362"), MU_S_DIREC | MU_S_IRUSR | MU_S_IWUSR | MU_S_IXUSR | MU_S_IRGRP | MU_S_IXGRP | MU_S_IXGRP);
    createDirectory (&fs, 4, "slides", lookUpUserNumber ("xie"), lookUpGroupNumber ("362"), MU_S_DIREC | MU_S_IRUSR | MU_S_IXUSR);
    createFile (&fs, 4, "something.cpp", lookUpUserNumber ("hogg"), lookUpGroupNumber ("362"), MU_S_REGLR | MU_S_IRUSR | MU_S_IRGRP, "zxcvbn", 54);
    createFile (&fs, 5, "handout.tar", lookUpUserNumber ("zoppetti"), lookUpGroupNumber ("362"), MU_S_REGLR | MU_S_IWUSR, "123", 54321);
    createFile (&fs, 6, "heaps.pdf", lookUpUserNumber ("xie"), lookUpGroupNumber ("362"), MU_S_REGLR | MU_S_IRUSR | MU_S_IWUSR | MU_S_IRGRP | MU_S_IROTH, "987654321", 24);

    // Set up basic filesystem data.
    int fd = open (diskName, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    write (fd, &fs, BLOCK_COUNT * BLOCK_SIZE);
    close (fd);
}

void
format (struct entireFileSystem* fs)
{
    // Clear out everything.
    assert (sizeof (struct entireFileSystem) == BLOCK_COUNT * BLOCK_SIZE);
    memset (fs, 0, BLOCK_COUNT * BLOCK_SIZE);

    // Set superblock contents.
    strcpy (fs->superblock, VERSION10);

    // Set all data blocks free, all others used.
    for (int blockNum = 0; blockNum < BLOCK_COUNT; ++blockNum)
    {
        fs->freeBlockMap[blockNum] = (blockNum < FIRSTDATABLOCK_NUMBER ? BLOCK_USED : BLOCK_AVAILABLE);
    }

    // Set every inode to available.
    for (int iNodeNumber = 0; iNodeNumber < INODE_COUNT; ++iNodeNumber)
    {
        fs->iNodes[iNodeNumber].mode = MU_S_AVAIL;
    }

    // Create an empty root directory.
    createDirectory (fs, -1, "", lookUpUserNumber ("root"), lookUpGroupNumber ("admin"), MU_S_DIREC | MU_S_IRWXU | MU_S_IRWXG | MU_S_IROTH | MU_S_IXOTH);
}

void
createDirectory (struct entireFileSystem* fs, int parentINodeNum, char* name, int userId, int groupId, int mode)
{
    assert ((mode & MU_S_REGLR) == 0);
    assert ((mode & MU_S_AVAIL) == 0);
    int chosenINodeNum = findAvailableINode (fs);
    fs->iNodes[chosenINodeNum].userOwner = userId;
    fs->iNodes[chosenINodeNum].groupOwner = groupId;
    fs->iNodes[chosenINodeNum].linkCount = 0;
    fs->iNodes[chosenINodeNum].size = 0;
    fs->iNodes[chosenINodeNum].mode = mode | MU_S_DIREC;

    createLink (fs, chosenINodeNum, chosenINodeNum, ".");
    createLink (fs, chosenINodeNum, parentINodeNum >= 0 ? parentINodeNum : chosenINodeNum, "..");
    if (parentINodeNum >= 0)
    {
        createLink (fs, parentINodeNum, chosenINodeNum, name);
    }
}

int
findAvailableINode (struct entireFileSystem* fs)
{
    for (int iNodeNumber = 0; iNodeNumber < INODE_COUNT; ++iNodeNumber)
    {
        if (fs->iNodes[iNodeNumber].mode & MU_S_AVAIL)
        {
            return iNodeNumber;
        }
    }
    return -1;
}

void
createLink (struct entireFileSystem* fs, int dirINode, int contentINode, const char* name)
{
    assert (0 <= dirINode && dirINode < INODE_COUNT);
    assert (0 <= contentINode && contentINode < INODE_COUNT);
    assert (fs->iNodes[dirINode].mode & MU_S_DIREC);

    int offsetInBlock = fs->iNodes[dirINode].size % BLOCK_SIZE;
    int blockIndex = fs->iNodes[dirINode].size / BLOCK_SIZE;

    // Allocate additional data block for directory if needed.
    if (offsetInBlock == 0)
    {
        int nextBlockNumber = findAvailableDataBlock (fs);
        fs->freeBlockMap[nextBlockNumber] = BLOCK_USED;    
        fs->iNodes[dirINode].directBlocks[blockIndex] = nextBlockNumber;
    }

    // Write new directory entry.
    int blockNumber = fs->iNodes[dirINode].directBlocks[blockIndex];
    char* pointer = fs->dataBlocks[blockNumber - FIRSTDATABLOCK_NUMBER] + offsetInBlock;
    struct dirEntry entry;
    entry.iNodeNumber = contentINode;
    memset (entry.name, 0, MAX_NAME_LENGTH);
    strncpy (entry.name, name, MAX_NAME_LENGTH - 1);
    memcpy (pointer, &entry, DIR_ENTRY_LENGTH);

    // Update inodes.
    fs->iNodes[dirINode].size += DIR_ENTRY_LENGTH;
    ++fs->iNodes[contentINode].linkCount;
}

int
findAvailableDataBlock (struct entireFileSystem* fs)
{
    for (int blockNumber = FIRSTDATABLOCK_NUMBER; blockNumber < BLOCK_COUNT; ++blockNumber)
    {
        if (fs->freeBlockMap[blockNumber] == BLOCK_AVAILABLE)
        {
            return blockNumber;
        }
    }
    return -1;
}

int
findINode (struct entireFileSystem* fs, int currentINodeNumber, const char* name)
{
    assert (0 <= currentINodeNumber && currentINodeNumber < INODE_COUNT);
    if (name == NULL || strcmp (name, "") == 0)
    {
        return currentINodeNumber;
    }
    assert (fs->iNodes[currentINodeNumber].mode & MU_S_DIREC);
    const char* start = name;
    if (start[0] == '/')
    {
        ++start;
    }
    const char* finish = strchr (start, '/');
    char buffer[MAX_NAME_LENGTH];
    if (finish == NULL)
    {
        strcpy (buffer, start);
    }
    else
    {
        memset (buffer, 0, MAX_NAME_LENGTH);
        strncpy (buffer, start, finish - start);
    }
    int totalBytesRead = 0;
    for (int blockIndex = 0; blockIndex < (fs->iNodes[currentINodeNumber].size + BLOCK_SIZE - 1) / BLOCK_SIZE; ++blockIndex)
    {
        int thisBlockBytesRead = 0;
        int blockNum = fs->iNodes[currentINodeNumber].directBlocks[blockIndex];
        struct dirEntry* entry = (struct dirEntry*)fs->dataBlocks[blockNum];
        while (totalBytesRead < fs->iNodes[currentINodeNumber].size && thisBlockBytesRead < BLOCK_SIZE)
        {
            if (strcmp (entry->name, buffer) == 0)
            {
                return findINode (fs, entry->iNodeNumber, finish);
            }
            ++entry;
            thisBlockBytesRead += DIR_ENTRY_LENGTH;
            totalBytesRead += DIR_ENTRY_LENGTH;
        }
    }
    assert (0);
}

void
createFile (struct entireFileSystem* fs, int parentINodeNum, char* name, int userId, int groupId, int mode, char* text, int size)
{
    assert ((mode & MU_S_DIREC) == 0);
    assert ((mode & MU_S_AVAIL) == 0);
    int chosenINodeNum = findAvailableINode (fs);
    fs->iNodes[chosenINodeNum].userOwner = userId;
    fs->iNodes[chosenINodeNum].groupOwner = groupId;
    fs->iNodes[chosenINodeNum].linkCount = 0;
    fs->iNodes[chosenINodeNum].size = size;
    fs->iNodes[chosenINodeNum].mode = mode | MU_S_REGLR;

    int blockIndex = 0;
    int blockNum = 0;
    int blockPos = 0;
    for (int printed = 0; printed < size; ++printed)
    {
        if (printed % BLOCK_SIZE == 0)
        {
            int nextBlockNumber = findAvailableDataBlock (fs);
            fs->freeBlockMap[nextBlockNumber] = BLOCK_USED;    
            fs->iNodes[chosenINodeNum].directBlocks[blockIndex] = nextBlockNumber;
            blockNum = nextBlockNumber;
            blockPos = 0;
            ++blockIndex;
        }
        fs->dataBlocks[blockNum - FIRSTDATABLOCK_NUMBER][blockPos] = *(text + printed % strlen (text));
        ++blockPos;
    }   

    createLink (fs, parentINodeNum, chosenINodeNum, name);
}