// File: muusers.h
// Author: Chad Hogg
// Public interface of a library for managing users and groups.
// Note that this works quite differently from the real UNIX system calls for interacting
//   with users and groups.  It has been simplified for our benefit.
// Part of CSCI380 munix lab.

#ifndef MUUSERS_H
#define MUUSERS_H

#include <stdint.h>

// Returns the user number of the user whose name matches userName,
//   or -1 if there is no such user.
int
lookUpUserNumber (const char* userName);

// Returns the user name of the user whose number matches userNumber,
//   or NULL if there is no such user.
const char*
lookUpUserName (int userNumber);

// Returns the group number of the group whose name matches groupName.
//   or -1 if there is no such group.
int
lookUpGroupNumber (const char* groupName);

// Returns the group name of the group whose number matches groupNumber,
//   or NULL if there is no such group.
const char*
lookupUpGroupName (int groupNumber);

// Returns 1 if userNumber is a member of groupNumber,
//   or 0 otherwise.  (Including if that user/group does not exist.)
int
isUserInGroup (int userNumber, int groupNumber);


#endif//MUUSERS_H