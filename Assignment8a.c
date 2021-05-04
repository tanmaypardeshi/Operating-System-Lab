#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 2048

typedef struct shared
{
	int flag;
	char text[SIZE];
} Shared;

int main()
{
	int shmid, choice, running = 1;
	char buffer[SIZE];
	void *shared_memory = NULL;
	Shared *stuff;

	shmid = shmget(1234, sizeof(Shared), 0666 | IPC_CREAT);

	if (shmid == -1)
	{
		printf("Failed");
		return 0;
	}

	shared_memory = shmat(shmid, NULL, 0);

	stuff = (Shared *)shared_memory;

	while (running)
	{
		printf("\nProgram 8a\n");
		printf("1. Read\n");
		printf("2. Write\n");
		printf("3. Exit\n");
		printf("\nEnter your choice:- ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("\nYou wrote: %s", stuff->text);
			break;
		case 2:
			printf("\nEnter the string to write - ");
			scanf("\n");
			fgets(buffer, BUFSIZ, stdin);
			strncpy(stuff->text, buffer, SIZE);
			break;
		case 3:
			running = 0;
			break;
		default:
			printf("\n");
		}
	}
	if (shmdt(shared_memory) == -1)
	{
		printf("Failed\n");
		return 0;
	}
	return 0;
}