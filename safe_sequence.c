#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

int main()
{
	int max[SIZE][SIZE], need[SIZE][SIZE], allocation[SIZE][SIZE], available[SIZE];
	int completed[SIZE], safeSequence[SIZE];
	
	int i,j,p,r, process, count;
	
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
	
	do
	{
		printf("\n Max matrix:\tAllocation matrix:\n");
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
				allocation[process][j] = 0;
				max[process][j] = 0;
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
		printf("\nThe system is in an unsafe state!!");
	return 0;
}
	
	
	
	
