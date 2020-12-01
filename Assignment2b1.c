#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


void print_arr(int [],int);
void quick_sort(int [],int ,int);

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
	
	quick_sort(arr, 0, n-1);
	
	printf("\nSorted array is:- ");
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

void quick_sort(int arr[],int first,int last)
{

    int i,j,k,pivot,cmp=0,swap=0,temp;

    if(first<last)
    {
        pivot=first;
        i=first;
        j=last;

        while(i<j)
        {
            while(arr[i] <= arr[pivot] && i<last)
                i++;

            while(arr[j] > arr[pivot])
                j--;

            cmp++;
            if(i<j)
            {
                swap++;
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }

        temp=arr[pivot];
        arr[pivot]=arr[j];
        arr[j]=temp;

        quick_sort(arr,first,j-1);
        quick_sort(arr,j+1,last);
    }
}

