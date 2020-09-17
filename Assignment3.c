#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<time.h>

struct params
{
	int i,j,c;
};

void *multiply(void *);

int *a,*b,*result;

int main()
{

	int res,r1,c1,r2,c2,i,j,t;
	struct params *p;
	pthread_t *ta;

	printf("\nEnter the number of rows for Matrix 1 - ");
	scanf("%d",&r1);
	printf("Enter the number of columns for Matrix 1 - ");
	scanf("%d",&c1);
	printf("\nEnter the number of rows for Matrix 2 - ");
	scanf("%d",&r2);
	printf("Enter the number of columns for Matrix 2 - ");
	scanf("%d",&c2);

	if (c1 != r2)
	{
		printf("\nThe matrices can't be multiplied with each other.\n");
		exit(0);
	}
	a =  (int *)malloc(r1 * c1 * sizeof(int));
	b =  (int *)malloc(r2 * c2 * sizeof(int));
	result = (int *)malloc(r1 * c2 * sizeof(int));
	
	ta = (pthread_t *)malloc(r1 * c2 * sizeof(pthread_t));
	
	printf("\nEnter elements of first matrix - \n");
	for (i = 0; i < r1; i++)
	{
		for (j = 0; j < c1; j++)
		{
			printf("Enter element [%d][%d] - ",i,j);
			scanf("%d", (a + i*c1 + j));
		}
	}
	printf("\nEnter elements of second matrix - \n");
	for (i = 0; i < r2; i++)
	{
		for (j = 0; j < c2; j++)
		{
 			printf("Enter element [%d][%d] - ",i,j);
			scanf("%d", (b + i*c1 + j));
		}
	}
	
	printf("\nMatrix 1 is:- \n");
	for (i = 0; i < r1; i++)
	{ 
		for (j = 0; j <c1; j++)
		{
			printf("%d\t",*(a+i*c2+j));
		}
		printf("\n");
	}
	
	printf("\nMatrix 2 is:- \n");
	for (i = 0; i < r2; i++)
	{ 
		for (j = 0; j <c2; j++)
		{
			printf("%d\t",*(b+i*c2+j));
		}
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < r1; i++) 
	{
		for (j = 0; j <c2; j++)
		{
			p = (struct params*)malloc(sizeof(struct params));
			p->i=i;
			p->j=j;
			p->c=c2;
			res = pthread_create((ta+i*c2+j),NULL,multiply,p);
			if (res != 0) 
			{
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
		}
	}

	for (i = 0; i < r1; i++)
	{ 
		for (j = 0; j <c2; j++)
		{
			res = pthread_join(*(ta+i*c2+j), NULL);	
			if (res != 0) 
			{
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}
		}

	}
	printf("\nResultant is:- \n");
	for (i = 0; i < r1; i++)
	{ 
		for (j = 0; j <c2; j++)
			printf("%d\t",*(result+i*c2+j));
		printf("\n");
	}
}

void *multiply(void *arg) 
{
	int k;
	struct params *p = (struct params *)arg;
	printf("Thread ID is:- %ld\n", pthread_self());
	*(result + p->i*p->c + p->j)=0;
	for (k = 0; k < p->c; k++)
	{
		*(result + p->i*p->c + p->j) += *(a + p->i*p->c + k) **(b + k*p->c + p->j);
	}
	pthread_exit(NULL);
}

