// File: munix.h
// Author: Chad Hogg
// Declarations of system calls for interacting with files in Munix.
// Part of munix lab in CSCI380

#ifndef MUNIX_H
#define MUNIX_H

#include "muerrno.h"

// Initializes the data for the process that is being simulated.
// Params:
//   userName - The name of the user who is running the process.
//   groupName - The name of the group that will own new files created by this process.
// Returns:
//   0 on success, or -1 and sets muerrno
// Errors:
//   MU_E_NO_SUCH_USER if there is no user with that name.
//   MU_E_NO_SUCH_GROUP if there is no such group with that name.
//   MU_E_NOT_MEMBER if that user is not a member of that group.
int
muinit (const char* userName, const char* groupName);

// Changes the calling process's current working directory.
// Params:
//   dirName - A string containing the name of the directory to change to.
// Returns:
//   0 on success, or -1 and sets muerrno.
// Errors:
//   MU_E_BAD_NAME if dirName is blank or contains a '/' character.
//   MU_E_DOES_NOT_EXIST if dirName is not the name of an entry in the working directory.
//   MU_E_NOT_DIR if dirName is the name of a regular file in the working directory.
//   MU_E_PERMISSION if the user/group does not have execute permission on dirName.
int
mucd (const char* dirName);

// Opens a file from the current working directory.
// Params:
//   fileName - A string containing the name of the file to open.
//   flags - Either MU_O_RDONLY or MU_O_WRONLY or MU_O_RDWR.
// Returns:
//   A usable file descriptor on success, or -1 and sets muerrno.
// Errors:
//   MU_E_FULL_TABLE if the open file table is full.
//   MU_E_BAD_NAME if fileName is blank or contains a '/' character.
//   MU_E_DOES_NOT_EXIST if fileName is not the name of an entry in the working directory.
//   MU_E_NOT_REG is fileName is the name of a directory in the working directory.
//   MU_E_PERMISSION if the user/group does not have the permissions implied by flags.
int
muopen (const char* fileName, int flags);

// Closes an open file, writing any buffered data to disk.
// Params:
//   fd - The file descriptor of the file to close.
// Returns:
//   0 on success, or -1 and sets muerrno.
// Errors:
//   MU_E_INVALID_FD if the file desciptor does not refer to an open file.
int
muclose (int fd);

// Reads the next n bytes from the file into buffer.
// Params:
//   fd - The file descriptor of the file to read from.
//   buffer - An array into which the data should be copied.
//   n - The maximum number of bytes to read.
// Returns:
//   The number of bytes read on success, or -1 and sets muerrno.
// Errors:
//   MU_E_INVALID_FD if the file descriptor does not refer to an open file.
//   MU_E_PERMISSION if the file is not open for reading.
int
muread (int fd, char* buffer, int n);

// Writes the first n bytes from the buffer into the file (or fewer if not enough space).
// Params:
//   fd - The file descriptor of the file to write to.
//   buffer - An array from which the data should be copied.
//   n - The number of bytes to write.
// Returns:
//   The number of bytes written on success, or -1 and sets muerrno.
// Errors:
//   MU_E_INVALID_FD if the file descriptor does not refer to an open file.
//   MU_E_PERMISSION if the file is not open for writing.
int
muwrite (int fd, const char* buffer, int n);

// Prints one line for each file/directory in the current working directory.
// For directories, the first character will be 'd', while for regular files it will be '-'.
// The next 9 characters will be 3 groups of 'rwx' (user-group-other) where each symbol is
//   used if that permission is granted, or replaced by '-' if it is not.
// This is followed by a space and the name of the owning user, right-justified in a field
//   of 10 characters, then another space and the name of the owning group right-justified
//   in a field of 10 characters.
// After one more space, the file name appears.
void
muls ();

#endif//MUNIX_H