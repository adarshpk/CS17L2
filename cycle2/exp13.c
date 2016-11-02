// Date: 22/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 13 - READERS WRITERS PROBLEM
/* Solution to the Readers-Writers Problem using semaphores.
*/
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex,writeblock;
int data = 0,rcount = 0;

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sleep(rand()%4);
  sem_wait(&mutex);
  rcount = rcount + 1;
  if(rcount==1)
   sem_wait(&writeblock);
  sem_post(&mutex);

  printf("Data read by the reader %d is %d\n",f,data);
  sem_wait(&mutex);
  rcount = rcount - 1;
  if(rcount==0)
    sem_post(&writeblock);
  sem_post(&mutex);

}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sleep(rand()%4);
  sem_wait(&writeblock);
  data++;
  printf("Data writen by the writer %d is %d\n",f,data);
  sem_post(&writeblock);

}

int main()
{
  int i,b;  
  pthread_t rtid[15],wtid[15];
  sem_init(&mutex,0,1);
  sem_init(&writeblock,0,1);
  for(i=0;i<=10;i++)
  {
    pthread_create(&wtid[i],NULL,writer,(void *)i);
    pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=10;i++)
  {
    pthread_join(wtid[i],NULL);
    pthread_join(rtid[i],NULL);
  }
}
