#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5

enum
{
    THINKING,
    EATING,
    HUNGRY
} state[N];

pthread_mutex_t lock;
sem_t chopsticks[N];

void *philosopher(void *no);
void takeChopstick(int i);
void putChopstick(int i);
void think(int i);
void eat(int i);

int eatCount[N] = {0};

void main()
{
    int *arg, i, result;

    result = pthread_mutex_init(&lock, NULL);

    pthread_t philosopherThread;

    for (i = 0; i < N; i++)
    {
        result = sem_init(&chopsticks[i], 0, 1);
        if (result != 0)
        {
            printf("\nCould not initialise chopsticks");
        }
    }
    for (i = 0; i < N; i++)
    {
        arg = (int *)malloc(sizeof(int));
        *arg = i;

        result = pthread_create(&philosopherThread, NULL, philosopher, (void *)arg);
        
        if (result != 0)
        {
            printf("\nCould not initialise philosopher");
        }
    }

    for (i = 0; i < N; i++)
    {
        result = pthread_join(philosopherThread, NULL);
        if (result != 0)
        {
            printf("\nThread joining failed");
        }
    }
}

void *philosopher(void *arg)
{
    int i;
    i = *(int *)arg;
    printf("Philosoper %d Entered\n", i);
    while (1)
    {
        think(i);
        eat(i);
    }
}

void think(int i)
{
    if (state[i] == THINKING)
    {
        int temp = rand() % 7;
        temp = (temp == 0 ? 3 : temp);
        printf("\nPhilosopsher %d is thinking \n", i);
        sleep(temp); 
        state[i] = HUNGRY; 
    }
}

void takeChopstick(int i)
{
    sem_wait(&chopsticks[i]);
    sem_wait(&chopsticks[(i + 1) % N]);
}

void putChopstick(int i)
{
    sem_post(&chopsticks[i]);
    sem_post(&chopsticks[(i + 1) % N]);
}

void eat(int i)
{
    int temp = rand() % 7;
    temp = temp == 0 ? 3 : temp;
    
    int j;
    if (state[(i + 1) % N] != EATING && state[(i + (N - 1)) % N] != EATING && state[i] == HUNGRY)
    {
        state[i] = EATING;

        printf("\nPhilosopsher %d is EATING", i);
        takeChopstick(i);
        sleep(temp);
        eatCount[i]++;

        printf("\nPhilosopsher %d HAS DONE EATING", i);
        putChopstick(i);
        state[i] = THINKING;

        pthread_mutex_lock(&lock);
        printf("\n\nEat Count : [");
        for (j = 0; j < N; j++)
        {
            printf(" %d", eatCount[j]);
        }
        printf("]");
        pthread_mutex_unlock(&lock);
    }
}