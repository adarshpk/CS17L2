// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 10 - PRODUCER-CONSUMER PROBLEM
/* Solution to the producer-consumer problem using semaphores and a shared buffer (size=10).
Producer puts items into the buffer while consumer consumes those items.
Two threads act as the producer and the consumer.
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
    sem_t fillCount, emptyCount;
    int in,out;
} buf;

void *producer() {
    int i=1;
    while (1) {
        int item;
        item=rand()%100;
        sem_wait(&(buf.emptyCount));
        buf.b[buf.in]=item;
        printf("\nProduced at \tb[%d]:%d",buf.in,item);
        buf.in=(buf.in+1)%10;
        sem_post(&(buf.fillCount));
        sleep(item%4);
    }
}

void *consumer() {
    while (1) {
        int item;
        sem_wait(&(buf.fillCount));
        item=buf.b[buf.out];
        printf("\nConsumed from \tb[%d]:%d",buf.out,item);
        buf.out=(buf.out+1)%10;
        sem_post(&(buf.emptyCount));
        sleep(rand()%4);

    }
}

int main() {
    pthread_t tidp,tidc;
    sem_init(&(buf.emptyCount),0,10);
    sem_init(&(buf.fillCount),0,0);
    buf.in=0;
    buf.out=0;
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