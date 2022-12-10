// File: muusers.c
// Author: Chad Hogg
// Implementation of a library for looking up information about users and groups.
// Uses static arrays of users, groups, and memberships, for simplicity.
// See muusers.h for documentation.
// Part of CSCI380 munix lab.

#include <string.h>

#include "muusers.h"

struct userEntry
{
    uint16_t userNumber;
    const char* userName;
};

struct groupEntry
{
    uint16_t groupNumber;
    const char* groupName;
};

struct membership
{
    uint16_t userNumber;
    uint16_t groupNumber;
};

#define NUM_USERS 7
#define NUM_GROUPS 11
#define NUM_MEMBERSHIPS 25

const struct userEntry USERS[NUM_USERS] = 
{
    {1, "root"},
    {2, "zoppetti"},
    {3, "schwartz"},
    {4, "hardy"},
    {5, "hogg"},
    {6, "xie"},
    {7, "cain"}
};

const struct groupEntry GROUPS[NUM_GROUPS] =
{
    {1, "admin"},
    {2, "140"},
    {3, "161"},
    {4, "162"},
    {5, "330"},
    {6, "340"},
    {7, "362"},
    {8, "366"},
    {9, "370"},
    {10, "380"},
    {11, "420"}
};

const struct membership MEMBERSHIPS[NUM_MEMBERSHIPS] =
{
    {1, 1},
    {2, 3}, {2, 7}, {2, 9}, {2, 10},
    {3, 3}, {3, 5}, {3, 6}, {3, 11},
    {4, 2}, {4, 3}, {4, 6},
    {5, 3}, {5, 4}, {5, 7}, {5, 8}, {5, 9},
    {6, 2}, {6, 3}, {6, 7},
    {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 11}
};

int
lookUpUserNumber (const char* userName)
{
    for (int index = 0; index < NUM_USERS; ++index)
    {
        if (strcmp (USERS[index].userName, userName) == 0)
        {
            return USERS[index].userNumber;
        }
    }
    return -1;
}

const char*
lookUpUserName (int userNumber)
{
    for (int index = 0; index < NUM_USERS; ++index)
    {
        if (USERS[index].userNumber == userNumber)
        {
            return USERS[index].userName;
        }
    }
    return NULL;
}

int
lookUpGroupNumber (const char* groupName)
{
    for (int index = 0; index < NUM_GROUPS; ++index)
    {
        if (strcmp (GROUPS[index].groupName, groupName) == 0)
        {
            return GROUPS[index].groupNumber;
        }
    }
    return -1;
}

const char*
lookupUpGroupName (int groupNumber)
{
    for (int index = 0; index < NUM_GROUPS; ++index)
    {
        if (GROUPS[index].groupNumber == groupNumber)
        {
            return GROUPS[index].groupName;
        }
    }
    return NULL;
}

int
isUserInGroup (int userNumber, int groupNumber)
{
    for (int index = 0; index < NUM_MEMBERSHIPS; ++index)
    {
        if (MEMBERSHIPS[index].userNumber == userNumber && MEMBERSHIPS[index].groupNumber == groupNumber)
        {
            return 1;
        }
    }
    return 0;
}