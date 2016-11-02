// Date: 22/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 14 - MONITORS
/* Using monitors to solve the producer-consumer problem using POSIX mutexes and POSIX condition variables.
*/
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

struct buffer
{
    int b[10];
    pthread_mutex_t monitor; // monitor lock
    pthread_cond_t empty;
    pthread_cond_t full;
    int in,out;
    int fullEntries;
} buf;

void *producer() {
    int i=1;
    while (1) {
        int item;
        item=rand()%100;
        pthread_mutex_lock(&buf.monitor);
        while (buf.fullEntries == 10)
            pthread_cond_wait(&buf.empty, &buf.monitor);
        buf.b[buf.in]=item;
        printf("\nProduced at \tb[%d]:%d",buf.in,item);
        buf.in=(buf.in+1)%10;
        buf.fullEntries++;
        pthread_cond_signal(&buf.full);
        pthread_mutex_unlock(&buf.monitor);
        sleep(item%4);
    }
}

void *consumer() {
    while (1) {
        int item;
        pthread_mutex_lock(&buf.monitor);
        while (buf.fullEntries == 0)
            pthread_cond_wait(&buf.full, &buf.monitor);
        item=buf.b[buf.out];
        printf("\nConsumed from \tb[%d]:%d",buf.out,item);
        buf.out=(buf.out+1)%10;
        buf.fullEntries--;
        pthread_cond_signal(&buf.empty);
        pthread_mutex_unlock(&buf.monitor);
        sleep(rand()%4);

    }
}

int main() {
    pthread_t tidp,tidc;
    buf.in=0;
    buf.out=0;
    buf.fullEntries=0;
    if(pthread_create(&tidp,NULL,producer,NULL)) {
        fprintf(stderr, "Error creating producer.\n");
        return 1;
    }
    if(pthread_create(&tidc,NULL,consumer,NULL)) {
        fprintf(stderr, "Error creating producer.\n");
        return 1;
    }
    pthread_join(tidp,NULL);
    pthread_join(tidc,NULL);
    sleep(5);
    exit(0);
}