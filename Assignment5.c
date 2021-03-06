#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#define BUFFERSIZE 10

sem_t rwlock,mutex;

void *reader_thread(void *no);
void *writer_thread(void *no);

int readcount, buffer[BUFFERSIZE], rid, wid;

int main()
{

	int res,nor,now,i;
	int *arg;
	pthread_t reader,writer;
	
	printf("\nReader and Writer Problem");
	printf("\nEnter the number of readers:- ");
	scanf("%d",&nor);
	printf("\n Enter the number of writers:- ");
	scanf("%d",&now);


	res =  sem_init(&rwlock, 0, 1);
    if (res != 0) 
    {
		printf("\nSemaphore initialization failed");
		printf("\nFailed to proceed");
		return 0;
	}	

	res = sem_init(&mutex, 0, 1);
	if (res != 0) 
    {
		printf("\nSemaphore initialization failed");
		printf("\nFailed to proceed");
		return 0;
	}	

	readcount = 0;
	rid = 0;
	wid = 0;
	
	printf("\nCreating Reading Threads");
	for(i=1;i<=nor;i++)
    {		
		printf("\nCreating Reader number %d",i);
		arg = (int *)malloc(sizeof(int));
		*arg = i;
		res = pthread_create(&reader,NULL,reader_thread,arg);
		if (res != 0) 
        {
			printf("\nThread Creation failed");
			printf("\nFailed to proceed");
			return 0;
		}	
	}

	printf("\nCreating Writer Threads");
	for(i=1;i<=now;i++)
    {		
		printf("\nCreating Writer number %d",i);	
		arg = (int *) malloc(sizeof(int));
		*arg = i;
		res = pthread_create(&writer,NULL,writer_thread,arg);	
		if (res != 0) 
        {
			printf("\nThread Creation failed");
			printf("\nFailed to proceed");
			return 0;
		}	
	}
	
	res = pthread_join(reader, NULL);		
	if (res != 0) 
    {
		printf("\nThread Waiting failed");
		printf("\nFailed to proceed");
		exit(EXIT_FAILURE);
	}

	res = pthread_join(writer, NULL);		
	if (res != 0) 
    {
		printf("\nThread Waiting failed");
		printf("\nFailed to proceed");
		exit(EXIT_FAILURE);
	}	
}

void *reader_thread(void *no)
{
	int *num = (int*) no;
	int i;
		
	while(1)
    {
		
        sleep(2);
		
        // Entry code
		sem_wait(&mutex);
        readcount++;
        if(readcount == 1)		
            sem_wait(&rwlock);
		sem_post(&mutex);

        // Critical section
		printf("\n\n\nEntered in reader number %d",*num);
		buffer[rid] = 0;
		printf("\n[ ");
		for(i=0;i<BUFFERSIZE;i++)
		{
			printf(" %d ", buffer[i]);
		}
		printf(" ]\n");
		rid = (rid + 1)%BUFFERSIZE;
        
		// Exit code
    	printf("\nExited from reader number %d",*num);
		sem_wait(&mutex);
        readcount--;
        if(readcount == 0)		
            sem_post(&rwlock);
		sem_post(&mutex);
	}	
}

void *writer_thread(void *no)
{
	int *num = (int*) no;
	while(1)
    {
		int temp = rand()%7,i;
		
        sleep(2);

        // Entry code
	    sem_wait(&rwlock);

        // Critical section
        printf("\n\n\nEntered in writer number %d",*num);
        buffer[wid] = *num;
		printf("\n[ ");
		for(i=0;i<BUFFERSIZE;i++)
		{
			printf(" %d ", buffer[i]);
		}
    	printf(" ]\n");
        wid = (wid + 1)%BUFFERSIZE;
		printf("\nThe data was changed");		

        // Exit code 
        printf("\nExited from writer number %d",*num);
		sem_post(&rwlock);		
	}	
}