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

int buffer[BUFFERSIZE];

int main() 
{

  int res;
  pthread_t tP,tC;

  sem_init(&mutex, 0, 1);
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, BUFFERSIZE);

  if (&full == SEM_FAILED) 
  {
	perror("Full Semaphore initialization failed");
	exit(EXIT_FAILURE);
  }

  if (&empty == SEM_FAILED) 
  {
	perror("Empty Semaphore initialization failed");
	exit(EXIT_FAILURE);
  }

  res=pthread_create(&tP, NULL, producer, NULL);
  res=pthread_create(&tC, NULL, consumer, NULL);
  res=pthread_join(tP, NULL);
  res=pthread_join(tC, NULL);


  sem_destroy(&full);
  sem_destroy(&empty);
  exit(EXIT_SUCCESS);
}

void *producer(void *arg) 
{

  int i=0,n;
  while(1) 
  {
    i++;
    sem_wait(&empty);
    sem_wait(&mutex);
    sem_getvalue(&full, &n);
    buffer[n] = i;
    printf("Produced: %d\n\n",i);
    sem_post(&mutex);
    sem_post(&full);
    sleep(1);
  }
  pthread_exit(NULL);
}

void *consumer(void *arg) 
{

  int n;
  while(1) 
  {
    sem_wait(&full);
    sem_wait(&mutex);
    sem_getvalue(&full, &n);
    printf("Consumed: %d\n\n",buffer[n]);
    sem_post(&mutex);
    sem_post(&empty);
    sleep(1);
  }
  pthread_exit(NULL);
}
