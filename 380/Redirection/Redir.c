/**
 * @file Redir.c
 * @author John "Matt" Shenk
 * @brief A program to demonstrates the functionality of creating new processes and using pipes to receive/send input/output 
            
        Commands to test with:

        date | tr '\n' '\t\t' >> userlog.txt ; ps -Ao user | tail -n +2 | sort | uniq | wc -l >> userlog.txt

 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Local includes
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

const char fileName[] = "userlog.txt";

int 
main(int argc, char *argv[]){
    // Create 5 pipes
    int pipe1[2], pipe2[2], pipe3[2], pipe4[2], pipe5[2];
    int status;
    int pid, out;
    
    pipe(pipe1);
    pid = fork(); //////////////////////////////// First Child


            
    if(pid < 0){
        
        fprintf(stderr, "Fork Error... Exiting");;
        exit(EXIT_FAILURE);

    }
    else if(pid == 0){
        char *commandArgs[] = {"date" ,NULL};

        dup2(pipe1[1], 1);
        close(pipe1[0]);
        execvp(*commandArgs, commandArgs);

        exit(EXIT_SUCCESS);
    }

    pid = fork(); //////////////////////////////// Second Child

    if(pid < 0){
        fprintf(stderr, "Fork Error... Exiting");;
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        
        char *commandArgs[] = {"tr", "'\n'", "'\t\t'",NULL};

        dup2(pipe1[0], 0);
        close(pipe1[1]);

        int fileOut = open(fileName, O_WRONLY | O_CREAT | O_APPEND,  S_IRWXU);
        dup2(fileOut, 1);
        close(fileOut);
        execvp(*commandArgs, commandArgs);
 
        exit(EXIT_SUCCESS);
    }        

    close(pipe1[1]);
    close(pipe1[0]);
    waitpid(pid, &status, 0); // Wait for Second Child to complete 
    pipe(pipe2);

    pid = fork(); //////////////////////////////// Third Child
    if(pid < 0){
        fprintf(stderr, "Fork Error... Exiting");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        close(pipe2[0]);

        char *commandArgs[] = {"ps", "-Ao", "user",NULL};
        
        dup2(pipe2[1], 1);
        
        execvp(*commandArgs, commandArgs);
        
        exit(EXIT_SUCCESS);
    }

    pipe(pipe3);

    pid = fork(); //////////////////////////////// Fourth Child

    if(pid < 0){
        fprintf(stderr, "Fork Error... Exiting");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        close(pipe2[1]);
        char *commandArgs[] = {"tail", "-n", "+2", NULL};
    
        dup2(pipe2[0], 0);
        close(pipe2[0]);

        dup2(pipe3[1], 1);
        close(pipe3[0]);

        execvp(*commandArgs, commandArgs);

        exit(EXIT_SUCCESS);
    }

    close(pipe2[1]);
    close(pipe2[0]);

    pipe(pipe4);

    pid = fork(); //////////////////////////////// Fifth Child

    if(pid < 0){
        fprintf(stderr, "Fork Error... Exiting");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        close(pipe3[1]);
        close(pipe4[0]);

        char *commandArgs[] = {"sort",NULL};

        dup2(pipe3[0], 0);
        close(pipe3[0]);


        dup2(pipe4[1], 1);
        close(pipe4[1]);

        execvp(*commandArgs, commandArgs);

        exit(EXIT_SUCCESS);
    }

    close(pipe3[1]);
    close(pipe3[0]);
    pipe(pipe5);
    pid = fork(); //////////////////////////////// Sixth Child

    if(pid < 0){
        fprintf(stderr, "Fork Error... Exiting");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        close(pipe4[1]);
        close(pipe5[0]);
        
        char * commandArgs[] = {"uniq", NULL};

        dup2(pipe4[0], 0);
        close(pipe4[0]);

        dup2(pipe5[1], 1);
        close(pipe5[1]);

        execvp(*commandArgs, commandArgs);

        exit(EXIT_SUCCESS);
    }

    close(pipe4[0]);
    close(pipe4[1]);
    pid = fork(); //////////////////////////////// Seventh Child

    if(pid < 0){
        fprintf(stderr, "Fork Error... Exiting");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        close(pipe5[1]);

        char * commandArgs[] = {"wc", "-l", NULL};

        dup2(pipe5[0], 0);
        close(pipe5[0]);

        int fileOut = open(fileName, O_WRONLY | O_CREAT | O_APPEND,  S_IRWXU);
        dup2(fileOut, 1);
        close(fileOut);

        execvp(*commandArgs, commandArgs);
 
        exit(EXIT_SUCCESS);
    }
    
    // wait for all children
    /*
    for(int i = 0; i < 6; i++)
        wait(&pid); 
    */
    close(pipe5[0]);
    close(pipe5[1]);
    waitpid(pid, &status, 0);

    exit(0);
}