#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFERSIZE 10

void *producer(void *arg);
void *consumer(void *arg);

sem_t empty;
sem_t full;
sem_t mutex;

int buffer[BUFFERSIZE], pid, cid;

int main() 
{

  int res, i, nproducer, nconsumer, *arg;
  pthread_t tproducer,tconsumer;

  printf("\nProducer and Consumer problem:- ");
  printf("\n\nEnter the number of producers:- ");
  scanf("%d", &nproducer);
  printf("Enter the number of consumer:- ");
  scanf("%d", &nconsumer);

  res = sem_init(&empty, 0, BUFFERSIZE);
  if(res != 0) 
  {
    printf("\nSemaphore initialisation failed");
    printf("\nFailed to proceed");
    exit(EXIT_FAILURE);
  }

  res = sem_init(&full, 0, 0);
  if(res != 0) 
  {
    printf("\nSemaphore initialisation failed");
    printf("\nFailed to proceed");
    exit(EXIT_FAILURE);
  }

  res = sem_init(&mutex, 0, 1);
  if(res != 0) 
  {
    printf("\nSemaphore initialisation failed");
    printf("\nFailed to proceed");
    exit(EXIT_FAILURE);
  }

  pid = 0;
  cid = 0;

  printf("\nCreating producer threads");
  for(i=1;i<=nproducer;i++)
  {
    printf("\nCreating prodcuer number:- %d", i);
    arg = (int*)malloc(sizeof(int));
    *arg = i;
    res = pthread_create(&tproducer, NULL, producer, arg);
    if(res != 0)
    {
      printf("\nThread initialisation failed");
      printf("\nFailed to proceed");
      exit(EXIT_FAILURE);
    }
  }

  printf("\nCreating consumer threads");
  for(i=1;i<=nconsumer;i++)
  {
    printf("\nCreating consumer number:- %d", i);
     arg = (int*)malloc(sizeof(int));
    *arg = i;
    res = pthread_create(&tconsumer, NULL, consumer, arg);
    if(res != 0)
    {
      printf("\nThread initialisation failed");
      printf("\nFailed to proceed");
      exit(EXIT_FAILURE);
    }
  }

  res = pthread_join(tproducer, NULL);
  if(res != 0)
  {
    printf("\nThread waiting failed");
    printf("\nFailed to proceed");
    exit(EXIT_FAILURE); 
  }

  res = pthread_join(tconsumer, NULL);
  if(res != 0)
  {
    printf("\nThread waiting failed");
    printf("\nFailed to proceed");
    exit(EXIT_FAILURE); 
  }

}

void *producer(void *arg) 
{
  int *num = (int *)arg;
  int i;
  while(1) 
  {
    sem_wait(&empty);
    sem_wait(&mutex);
    printf("\nEntered in producer %d", *num);
    buffer[pid] = *num;  
    printf("\n[ ");
    for(i=0;i<BUFFERSIZE;i++)
    {
        printf(" %d ", buffer[i]);
    }
    printf(" ]\n");
    printf("Exited in producer %d\n", *num);
    pid = (pid + 1)%BUFFERSIZE;
    sem_post(&mutex);
    sem_post(&full);
    sleep(4);
  }
  pthread_exit(NULL);
}

void *consumer(void *arg) 
{
  int *num = (int *)arg;
  int i;
  while(1) 
  {
    sem_wait(&full);
    sem_wait(&mutex);
    printf("\nEntered in consumer %d", *num);
    buffer[cid] = 0;
    printf("\n[ ");
    for(i=0;i<BUFFERSIZE;i++)
    {
        printf(" %d ", buffer[i]);
    }
    printf(" ]\n");
    cid = (cid + 1)%BUFFERSIZE;
    printf("Exited in consumer %d\n", *num);
    sem_post(&mutex);
    sem_post(&empty);
    sleep(4);
  }
  pthread_exit(NULL);
}
