// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 8 - FAMILIARISATION OF POSIX SEMAPHORE SYSTEM CALLS
/* Create two threads, each incrementing a common varaiable by 1000000 one step at a time.
Semaphores are used to ensure mutual exclusion and reach the final value of 2000000
Additionally, on a signal, the signal handler makes the thread lock the semaphore 
which is already locked by itself creating a deadlock.*/
// ADARSH P.K. CSU13203

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int countVal = 0, semVal;
sem_t mutex;

void make_wait() {
   sem_wait(&mutex);
   printf("\nThread %lu tries to lock the semaphore.\nThis will create a deadlock!", pthread_self());
   fflush(stdout);
}

void *count()
{
    int i;
    printf("Log: Count thread %lu\n", pthread_self());
    fflush(stdout);
    for(i=0; i<1000000; i++)
    {
        sem_wait(&mutex);
        if(countVal == 58659) {
          sem_getvalue(&mutex, &semVal); 
          printf("\nAt countVal=%d, semVal is %d inside critical region.\n", countVal,semVal);
          sleep(5);
        }
        countVal++;
        sem_post(&mutex);
    }
    return 0;
}

int main()
{
    signal(SIGINT, make_wait); 
    sem_init(&mutex,0,1);
    sem_getvalue(&mutex, &semVal); 
    printf("\nInitially, semVal is %d outside critical region.\n", semVal);
    pthread_t thread1;
        printf("Log: Initial thread %lu\n", pthread_self());

    if(pthread_create(&thread1, NULL, count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }
    // if(pthread_create(&thread2, NULL, count, NULL))
    // {
    //   printf("\n ERROR creating thread 2");
    //   exit(1);
    // }
    count();
    if(pthread_join(thread1, NULL))
    {
      printf("\n ERROR joining thread 1");
      exit(1);
    }

    // if(pthread_join(thread2, NULL))
    // {
    //   printf("\n ERROR joining thread 2");
    //   exit(1);
    // }
    sem_destroy(&mutex);     
    printf("\nSemaphore destroyed!\n");
    if (countVal < 2000000) 
        printf("\nThe value of countVal is [%d], should be 2000000.\n\n", countVal);
    else
        printf("\nThe value of countVal is [%d].\n\n", countVal);

    pthread_exit(NULL);
}

