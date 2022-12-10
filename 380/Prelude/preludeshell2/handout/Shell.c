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

// For waiting 
#include <sys/wait.h>

// Global constants
const int MAX_SIZE = 80; // Maximum size of input string
const int MAX_ARGS = 5;  // Maximum arguments

int main ()
{
    char words[MAX_SIZE];
    char *args[MAX_ARGS];
    
    printf("shell> ");
    fgets(words, MAX_SIZE, stdin); // Ensure a max size of 80
   
    // Tokenize the string, delimited by space, tab, and newline characters
    //Get first token
    char *token  = strtok(words, " \n");
    int n = 0;

    while(token != NULL){
        args[n] = token;
        token = strtok(NULL, " \n");
        if(token == NULL)
            args[n+1] = token;
        n++;
    }

    pid_t pid = fork ();
    if (pid < 0) 
    {
        fprintf (stderr, "fork error (%s) -- exiting\n",
	        strerror (errno));
        exit (1);
    }
    if (pid == 0) //Child process
    {
        printf("[ %s ] (PID: %d)\n", args[0], getpid());
        
        int ret = execvp (args[0], args); 

        if (ret < 0)
        {
            fprintf (stderr, "exec error (%s) -- exiting\n",
	        strerror (errno));
            exit (1);
        }
        exit (0);
    }

 
   int s;
   waitpid(pid, &s, WUNTRACED);
   printf("[* %s *] (Exit: %d)\n", args[0], WEXITSTATUS(s));
    
    return 0;
}