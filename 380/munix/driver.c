// File: driver.c
// Author: Chad Hogg
// A simple REPL for testing our pseudo-system calls.
// Part of CSCI380 munix lab.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "munix.h"
#include "mufs.h"
#include "muerrno.h"

#define BUFFER_LENGTH 1024

int
main (int argc, char* argv[])
{
    char buffer[BUFFER_LENGTH];
    char userName[BUFFER_LENGTH];
    char groupName[BUFFER_LENGTH];
    printf ("Disk name: ");
    fgets (buffer, BUFFER_LENGTH, stdin);
    buffer[strlen (buffer) - 1] = '\0';
    setup (buffer);
    printf ("user name: ");
    fgets (userName, BUFFER_LENGTH, stdin);
    userName[strlen (userName) - 1] = '\0';
    printf ("Group name: ");
    fgets (groupName, BUFFER_LENGTH, stdin);
    groupName[strlen (groupName) - 1] = '\0';
    if (muinit (userName, groupName) < 0)
    {
        printf ("MU Error initializing system: %d\n", muerrno);
        exit (EXIT_FAILURE);
    }
    printf ("> ");
    fgets (buffer, BUFFER_LENGTH, stdin);
    buffer[strlen (buffer) - 1] = '\0';
    while (!strcmp (buffer, "quit") == 0)
    {
        char* command = strtok (buffer, " ");
        if (command != NULL)
        {
            if (strcmp (command, "cd") == 0 || strcmp (command, "mucd") == 0)
            {
                char* name = strtok (NULL, " ");
                if (name == NULL)
                {
                    printf ("No directory specified.\n");
                }
                else if (mucd (name) < 0)
                {
                    printf ("Could not change directory: %d\n", muerrno);
                }
            }
            else if (strcmp (command, "open") == 0 || strcmp (command, "muopen") == 0)
            {
                char* name = strtok (NULL, " ");
                char* flagsStr = strtok (NULL, " ");
                if (name == NULL)
                {
                    printf ("No file name provided.\n");
                }
                else if (flagsStr == NULL)
                {
                    printf ("No flags provided.\n");
                }
                else
                {
                    int flags = 0;
                    if (strchr (flagsStr, 'r') != NULL) { flags |= MU_O_RDONLY; }
                    if (strchr (flagsStr, 'w') != NULL) { flags |= MU_O_WRONLY; }
                    if (flags == 0)
                    {
                        printf ("Flags did not contain 'r' or 'w'.\n");
                    }
                    else
                    {
                        int fd = muopen (name, flags);
                        if (fd < 0)
                        {
                            printf ("Could not open file: %d\n", muerrno);
                        }
                        else
                        {
                            printf ("Opened file has descriptor %d\n", fd);
                        }
                    }
                }
            }
            else if (strcmp (command, "close") == 0 || strcmp (command, "muclose") == 0)
            {
                char* token = strtok (NULL, " ");
                if (token == NULL)
                {
                    printf ("No file descriptor provided.\n");
                }
                else
                {
                    int fd = atoi (token);
                    if (muclose (fd) < 0)
                    {
                        printf ("Could not close file: %d\n", muerrno);
                    }
                    else
                    {
                        printf ("Closed file.\n");
                    }
                }
            }
            else if (strcmp (command, "read") == 0 || strcmp (command, "muread") == 0)
            {
                char* file = strtok (NULL, " ");
                char* number = strtok (NULL, " ");
                if (file == NULL)
                {
                    printf ("No file descriptor provided.\n");
                }
                else if (number == NULL)
                {
                    printf ("No number of bytes provided.\n");
                }
                else
                {
                    int fd = atoi (file);
                    int desired = atoi (number);
                    char str[desired + 1];
                    memset (str, '\0', desired + 1);
                    int bytes = muread (fd, str, desired);
                    if (bytes < 0)
                    {
                        printf ("Could not read from file: %d\n", muerrno);
                    }
                    else
                    {
                        printf ("Read %s from file.\n", str);
                    }
                }
            }
            else if (strcmp (command, "write") == 0 || strcmp (command, "muwrite") == 0)
            {
                char* file = strtok (NULL, " ");
                if (file == NULL)
                {
                    printf ("No file descriptor provided.\n");
                }
                else
                {
                    int fd = atoi (file);
                    char* str = strtok (NULL, "\n");
                    if (str == NULL)
                    {
                        printf ("No string provided.\n");
                    }
                    else
                    {
                        int bytes = muwrite (fd, str, strlen (str));
                        if (bytes < 0)
                        {
                            printf ("Could not write to file: %d\n", muerrno);
                        }
                        else
                        {
                            printf ("Wrote %d bytes to file.\n", bytes);
                        }
                    }
                }
            }
            else if (strcmp (command, "ls") == 0 || strcmp (command, "muls") == 0)
            {
                muls ();
            }
            else {
                printf ("Unknown command %s\n", command);
            }
        }
        printf ("> ");
        fgets (buffer, BUFFER_LENGTH, stdin);
        buffer[strlen (buffer) - 1] = '\0';
    }

    teardown ();
    return EXIT_SUCCESS;
}