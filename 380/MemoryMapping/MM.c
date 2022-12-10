/**
 * @file MM.c
 * @author John "Matt" Shenk
 * @brief A program to implement a version of the 'cp' program using memory mapping
 *
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

int 
main(int argc, char *argv[]){
    int fd1, fd2;
    struct stat buffer;
    
    fd1 = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

    fd2 = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    fstat(fd1, &buffer);
    
    ftruncate(fd2, buffer.st_size);

    void *source = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    void *destination = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    
    memcpy(destination, source, buffer.st_size);

    munmap(destination, buffer.st_size);
    munmap(source, buffer.st_size);

    // Remember to close fide descriptors!
    close(fd1);
    close(fd2);

    // Show the destination file to see if it worked
    char *showText2[] = {"code", argv[2], NULL};
    execvp(showText2[0], showText2); 

    return 0;
}