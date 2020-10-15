#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

int max[SIZE][SIZE], need[SIZE][SIZE], allocation[SIZE][SIZE];
int completed[SIZE], safeSequence[SIZE], req[SIZE], available[SIZE];
int i,j,p,r, process, count, request, flag, choice;

void safesequence();
void requestresource();
	
int main()
{
	printf("Enter the number of processes:- ");
	scanf("%d", &p);
	
	for(i = 0; i< p; i++)
		completed[i] = 0;
	
	printf("Enter the number of resources:- ");
	scanf("%d", &r);
	
	printf("Enter the max matrix for each process:- ");
	for(i=0;i<p;i++)
	{
		printf("\nFor process %d:- ", i+1);
		for(j=0;j<r;j++)
		{
			scanf("%d", &max[i][j]);
		}
	}
	
	printf("Enter the allocation for each process:- ");
	for(i=0;i<p;i++)
	{
		printf("\nFor process %d:- ", i+1);
		for(j=0;j<r;j++)
		{
			scanf("%d", &allocation[i][j]);
		}
	}
	
	printf("Enter the available resources:- ");
	for(i=0;i<r;i++)
	{
		scanf("%d", &available[i]);	
	}
	
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	
	while(1)
	{
		printf("\nBanker's Algorithm:- \n");
		printf("\n1. Check for safe sequence");
		printf("\n2. Request resource algorithm");
		printf("\n3. Exit the program\n");
		printf("\nEnter your choice:- ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				safesequence();
				break;
			case 2:
				requestresource();
				break;
			case 3:
				return 0;
			default:
				printf("\nError in choice, try again\n");
		}
	}
	return 0;
}
	
	
void safesequence()
{ 
	do
	{
		printf("\nMax matrix:\tAllocation matrix:\n");
		for(i = 0; i < p; i++)
		{
			for( j = 0; j < r; j++)
				printf("%d  ", max[i][j]);
			printf("\t\t");
			for( j = 0; j < r; j++)
				printf("%d  ", allocation[i][j]);
			printf("\n");
		}

		process = -1;

		for(i = 0; i < p; i++)
		{
			if(completed[i] == 0)//if not completed
			{
				process = i;
				for(j = 0; j < r; j++)
				{
					if(available[j] < need[i][j])
					{
						process = -1;
						break;
					}
				}
			}
			if(process != -1)
				break;
		}
		if(process != -1)
		{
			printf("\nProcess %d runs to completion!", process + 1);
			safeSequence[count] = process + 1;
			count++;
			for(j = 0; j < r; j++)
			{
				available[j] += allocation[process][j];
				completed[process] = 1;
			}
		}

	} while(count != p && process != -1);

	if(count == p)
	{
		printf("\nThe system is in a safe state!!\n");
		printf("Safe Sequence : < ");
		for( i = 0; i < p; i++)
				printf("%d  ", safeSequence[i]);
		printf(">\n");
	}
	else
		printf("\nThe system is in an unsafe state!!\n");
}

void requestresource()
{
	printf("Enter the process from 0 to %d for which request is to be made:- ", p-1);
	scanf("%d", &request);
	
	if(request < 0 || request >= p)
	{
		printf("\nInvalid");
		return;
	}
	
	printf("Enter resource request for process %d \n", request);
	for(i =0; i< r; i++)
	{
		printf("\nEnter request for resource %d:- ", i+1);
		scanf("%d", &req[i]);
	}
	
	for (j = 0; j < request; j++) 
	{
		flag = 0; 
		if (need[request][j] >= req[j])
		{ 
			if (req[j] <= available[j])
			{ 
                		available[j] = available[j] - req[j];
				allocation[request][j] += req[j];
				need[request][j] = need[request][j] - req[j];
				flag = 1;
			}
		} 
		
		if(!flag)
			break;
	}
	if(flag)
		safesequence();
}

	
	
	
