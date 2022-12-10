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

// For signal handler
#include <signal.h>

//For wait
#include <wait.h>

// Global constants
const int MAX_SIZE = 80; // Maximum size of input string
const int MAX_ARGS = 5;  // Maximum arguments

// Declaration for signal handler
void
handler(int signal);

int main ()
{
    char words[MAX_SIZE];
    char *args[MAX_ARGS];

    // Signal Handler
    if (signal (SIGCHLD, handler) == SIG_ERR)
    {
        fprintf (stderr, "signal error (%s) -- exiting\n",
	    strerror (errno));
        exit (1);
    }
    
    printf("shell> ");
    fgets(words, MAX_SIZE, stdin);

    while(strlen(words) < 2){
        strcpy(words, "");
        printf("shell> ");
        fgets(words, MAX_SIZE, stdin);
    }
   
    // Tokenize the string, delimited by space, tab, and newline characters
    //Get first token
    char *token  = strtok(words, " \n");
    int n = 0;
    // Get other tokens
    while(token != NULL){
        args[n] = token;
        token = strtok(NULL, " \n");
        if(token == NULL)
            args[n+1] = token;
        n++;
    }

    while(strcmp(args[0],"exit") != 0)
    {
        pid_t pid = fork ();
        
        if (pid < 0) 
        {
            fprintf (stderr, "fork error (%s) -- exiting\n",
                    strerror (errno));
            exit (1);
        }
        if (pid == 0) //Child process
        {
            printf("[ PID: %d ]\n", getpid());
        
            int ret = execvp (args[0], args); 

            if (ret < 0)
            {
                fprintf (stderr, "exec error (%s) -- exiting\n",
                    strerror (errno));
                exit (1);
            }
            exit (0);
        }
       
        strcpy(args[0], "");
        strcpy(words, "");
        
       
        while(strlen(words) < 2){
            sleep(2);
            printf("shell> ");
            fgets(words, MAX_SIZE, stdin);
        }
        
        token  = strtok(words, " \n");
        n = 0;

        while(token != NULL){
        args[n] = token;
        token = strtok(NULL, " \n");
        if(token == NULL)
            args[n+1] = token;
        n++;
        }
        
    }

    return 0;
}

// Implementation of signal handler
void
handler(int signal)
{
    pid_t pid;
    while((pid = waitpid(-1, &signal, WNOHANG)) != -1)
    {
        if(WIFEXITED(signal))
            printf("[ PID: %d (Exit: %d) ]\n", pid, WEXITSTATUS(signal));
        if(WIFSIGNALED(signal))
            printf("[ PID: %d (Signal %d) ]\n", pid, WTERMSIG(signal));
    }
}