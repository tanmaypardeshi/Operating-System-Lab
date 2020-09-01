#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


void print_arr(int [],int);

int main()
{

	int arr[100],n;
	pid_t child;

	printf("\nThis is the main process:- ");
	printf("\nProcess id %d",getpid());
	printf("\nParent id %d",getppid());

	printf("\n\nEnter the size of array:- ");
	scanf("%d",&n);
	
	printf("\nPlease enter the elements in the array in ascending order:-\n");
	for(int i=0; i<n; i++)
	{
		printf("Enter the element [%d]:- ",i);
		scanf("%d",&arr[i]);
	}

	printf("\nArray is:- ");
	print_arr(arr,n);
	printf("\n");


	printf("\nForking the current process");
	child = fork();

	if(child == -1)
		printf("\nChild not born");
		
	else if(child == 0)
	{
		printf("\nChild process!\n");
		
		char *buffer[n+1];
		int i;

		buffer[0] = "./binary";
				
		for(i=1;i<n+1;i++)
		{
			buffer[i] = malloc(20);
			snprintf(buffer[i], 20, "%d", arr[i-1]);
		}

		buffer[i] = NULL;

		execv("./binary",buffer);
		
		printf("Child executed successfully\n");
	}
	else
	{
		printf("\nParent process!\n");
		wait(NULL);
		printf("\nParent executed successfully\n\n");
	}
	return 0;
}


void print_arr(int arr[100],int n)
{
	int i;
	printf("[ ");

	for(i=0; i<n-1; i++)
		printf(" %d, ",arr[i]);

	printf(" %d ]",arr[i]);
}

