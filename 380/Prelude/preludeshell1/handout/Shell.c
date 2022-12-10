// An implementation of a simple shell program
// John Shenk

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

// For strerror
#include <string.h>

// For fork, getpid, execve, read, write, close,
//   and other Linux system calls
#include <unistd.h>
// For errno
#include <errno.h>

//Global constants
const int MAX_SIZE = 80; //Maximum size of input string

int main ()
{
    char words[MAX_SIZE];
    printf("shell> ");
    fgets(words, MAX_SIZE, stdin); //Ensure a max size of 80

    // Remove newline charcater
    strtok(words, "\n"); 

    pid_t pid = fork ();
    if (pid < 0) 
    {
        fprintf (stderr, "fork error (%s) -- exiting\n",
	        strerror (errno));
        exit (1);
    }
    if (pid == 0) //Child process
    {
        printf ("Child says: PID = %d, parent PID = %d, '%s' \n", getpid(), getppid(), words);
        exit (0); 
    }
    printf("Parent says: PID = %d, child PID = %d, parent PID = %d\n", getpid(), pid, getppid()); //Parent process
    /*
        The PID that spawned my processes is that of the bash shell on the linux machine I am using.
        This makes sense because I ran the program using a terminal command.
    */

    return 0;
}