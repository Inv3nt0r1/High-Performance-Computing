
#include<stdio.h>
#include<omp.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

int printRandoms(int lower, int upper) 
{ 
    int num = (rand()%(upper-lower+1))+lower; 
    return num;
}
int printArray(int array[], int total)
{
	for(int i=0;i<total;i++)
		printf("  %d  ",array[i]);
	printf("\n");
}
int main()
{
	printf("Enter Total number of elements in array: ");
	int total;
	scanf("%d",&total);
	int array[total], array_copy[total];
	clock_t start, end;
	double total_time_serial, total_time_parallel;
	for(int j=0;j<total;j++)
	{
		array[j]=printRandoms(0,10);
	}
	for(int j=0;j<total;j++)
	{
		array_copy[j]=array[j];
	}
	
	
	int j = 0;
	printf("\nArray before sorting: \n");
	
	printArray(array,total);
	bool odd_sorted = false;
	bool even_sorted = false;
	start = clock();
	for(int i=0;i<total;i++)
	{
		if(i%2==0)
			j=0;
		else
			j=1;
		#pragma omp parallel for
		for(int k=j;k<total;k=k+2)
		{
			if(array[k]>array[k+1])
			{
				if(j==0)
					even_sorted = true;
				else
					odd_sorted = true;
				int temp = array[k];
				array[k] = array[k+1];
				array[k+1] = temp;
			}
		}
		if(even_sorted == false && odd_sorted == false)
			break;
		even_sorted = odd_sorted = false;
	}
	end = clock();
	total_time_parallel = ((double) (end - start)/CLOCKS_PER_SEC);
	//calulate total time
	printf("\nArray After Serial sorting: \n");
	printArray(array,total);
	
	start = clock();
	for(int i=0;i<total;i++)
	{
		for(j=i;j<total;j++)
		{
			if(array_copy[j]>array_copy[j+1])
			{
				int temp = array_copy[j];
				array_copy[j] = array_copy[j+1];
				array_copy[j+1] = temp;
			}
		}
	}
	end = clock();
	printf("\nArray After Serial sorting: \n");
	printArray(array_copy,total);
	total_time_serial = ((double) (end - start)/CLOCKS_PER_SEC);
	
	printf("\nTotal Time Taken for parallel: %f\n", total_time_parallel);
	printf("\nTotal Time Taken for Serial: %f\n", total_time_serial);
	if(total_time_parallel < total_time_serial)
		printf("\nParallel Execution is faster. Serial took %f milliseconds longer than Serial.\n",total_time_serial-total_time_parallel);
	else
		printf("\nSerial Execution is faster. Parallel took %f milliseconds longer than Parallel.\n",total_time_parallel-total_time_serial);
	return 0;
}
