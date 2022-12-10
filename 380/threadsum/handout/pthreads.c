/**
 * @file pthreads.c
 * @author Matt Shenk
 * @brief A program showwcasing the usee of the pthread system call. 
 * @version 0.1
 * @date 2022-12-05
 * 
 * @copyright Copyright (c) 2022
 * :D
 */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int p;
int N;
int * A;

// Function for threads to use
void * threadSum(void * id);

int main(){
    int parallelSum = 0;
    int serialSum = 0;
    
    // Get p
    printf("p ==> ");
    scanf("%d", &p);

    // Get N
    printf("N ==> ");
    scanf("%d", &N);  

    // Change size of array to match N
    A = (int *)malloc(N * sizeof(int)); 
    
    // prepare threads
    pthread_t* threads = malloc (p * sizeof (pthread_t));   

    // populate array
    for(int x = 0; x < N; x++){
        int rnd = (rand() % 5);
        A[x] = rnd;
    } 

    // Send threads out to add
    for(long threadID = 0; threadID < p; threadID++){
        pthread_create (&threads[threadID], NULL,
		    threadSum, (void *) threadID);
    }

    // wait for threads & add return values to sum
    for(int threadID = 0; threadID < p; threadID++){
        void * retVal;
        pthread_join (threads[threadID], &retVal);
        parallelSum += (long) retVal;
    }

    printf("\nParallel Sum: %d\n", parallelSum);

    for(int i = 0; i < N; i++){
        serialSum += A[i];
    }
    printf("Serial Sum: %d\n", serialSum);
}

void *
threadSum(void * id){
    long tid = (long) id;
    long sum = 0;
    //printf("Thread %d says hi!\n", tid);
    int start;
    int end;

    // Calculate the starting index
    if(tid == 0)
        start = 0;
    else
        start = 0 + (N / p) * tid;

    // Calculate the ending index
    if(tid == 0)
        end = (N / p) - 1;
    else
        end = (0 + (N / p) * (tid + 1)) - 1;

    // Loop through starting to ending index,
    //  adding entries to sum
    for(int y = start; y <= end; y++){
        sum += A[y];
    }

    //printf("Thread %d sum: %d\n", tid, sum);
    void* result = (void *) sum;
    return result;
}