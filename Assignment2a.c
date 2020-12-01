#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>
#define SIZE 100


void print_arr(int [], int);
void quick_sort(int [], int, int);
void merge(int [], int, int, int);
void merge_sort(int [], int, int);


int main()
{

	int arr[SIZE],n,i,choice;
	pid_t newpid,child;
	char buffer[25];

	printf("\nThis is the main process:- ");
	printf("\nProcess id:- %d", getpid());
	printf("\nParent id:- %d", getppid());

	printf("\n\nEnter the size of array:- ");
	scanf("%d",&n);

	printf("\nPlease enter the elements in the array:- \n");
	for(int i=0;i<n;i++)
	{
		printf("Enter the element [%d]:- ", i);
		scanf("%d", &arr[i]);
	}
	printf("\nUnsorted array is:- ");
	print_arr(arr,n);

	printf("\n\nAssignment 2a - Orphan and Zombie process");
	printf("\n1. Zombie");
	printf("\n2. Orphan");
	printf("\n3. Exit program");
	printf("\n\nEnter your choice:- ");
	scanf("%d",&choice);

	printf("\nForking the process");
	newpid = fork();

	switch(choice)
	{
		case 1:			
			if(newpid == -1)
				printf("\nUnfortunately the child was not born");
			else if(newpid == 0)
			{
				printf("\n\nChild process!");
				printf("\nMy id is %d", getpid());		
				printf("\nSorted Array using quick sort:- ");
				quick_sort(arr,0,n-1);
				print_arr(arr,n);
				printf("\nChild executed successfully");
				printf("\nChild is now in zombie state\n\n");
			}
			else
			{
				sleep(10);
				printf("\n\nParent process!");
				printf("\nMy id is %d", getpid());
				printf("\nSorted Array using merge sort:- ");
				merge_sort(arr,0,n-1);
				print_arr(arr,n);
				printf("\n\nParent executed successfully\n");
				 system("ps -al | grep a.out");
				exit(0);
			}
			break;
		case 2:
			if(newpid == -1)
				printf("\nUnfortunately the child was not born");
			else if(newpid == 0)
			{
				printf("\n\nChild process!");
				printf("\nMy id is %d", getpid());
				printf("\nMy parent before sleep() is %d", getppid());
				printf("\nSorted Array using quick sort:- ");
				quick_sort(arr,0,n-1);
				print_arr(arr,n);
				sleep(10);
				printf("\nMy parent after sleep() is %d", getppid());	
				printf("\nChild executed successfully");
			}
			else
			{
				printf("\n\nParent process!");
				printf("\nMy id is %d", getpid());
				printf("\nSorted Array using merge sort:-  ");
				merge_sort(arr,0,n-1);
				print_arr(arr,n);
				printf("\nParent executed successfully");
				printf("\nParent died your child is now orphan\n\n");				
				exit(0);
			}
			break;
		case 3:
			return 0;
		default:
			printf("\nInvalid choice, please try again\n");
	}
	return 0;
}

void print_arr(int arr[], int n)
{
	int i;
	printf("[");
 
	for(i=0;i<n-1;i++)
		printf(" %d, ", arr[i]);

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

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void merge_sort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        merge_sort(arr, l, m); 
        merge_sort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

