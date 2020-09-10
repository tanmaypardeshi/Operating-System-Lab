/*
================================================================================
Assignment 2b Part 2: Binary Search
Name: Tanmay Pardeshi
Roll number: 33259
Batch: N 10
================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void binary_search(int [],int,int);

int main(int argc, char* argv[])
{

	int arr[argc-1],search;

	for(int i=1;i<argc;i++)
		arr[i-1]=atoi(argv[i]);


	printf("\nEnter the value to be searched:- ");
	scanf("%d",&search);

	binary_search(arr,argc-1,search);
	
	return 0;
}


void binary_search(int arr[100],int no,int search)
{
	int first,last,mid;
	first = 0;
	last = no-1;
	mid = (first + last)/2;

	while(first<=last){
		if(arr[mid] < search)
			first=mid+1;
		else if(arr[mid] == search){
			printf("\nElement was found in the array at location %d\n", mid);
			break;
		}
		else
			last = mid-1;
		mid = (first + last)/2;
	}

	if(first>last)
		printf("\nElement was not found in the array\n");
}

