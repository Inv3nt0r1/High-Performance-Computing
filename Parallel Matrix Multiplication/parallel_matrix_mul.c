

#include<stdio.h>
#include<omp.h>
#include <stdlib.h>
#include <time.h> 

int printRandoms(int lower, int upper) 
{ 
    int i; 
    int num = (rand()%(upper-lower+1))+lower; 
    return num;
} 

int main()
{
	int a[500][500],b[500][500],c[500][500];
	int m,n;
	clock_t start, end;
	double total_time_serial, total_time_parallel;
	
	printf("\n Enter the number of rows and Columns::");
	scanf("%d%d",&n,&m);
	//printf("\n Enter the elements of A::");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			
			a[i][j]=printRandoms(5,7);
		}
	}
	//printf("\n Enter the elements of B::");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{	
			
			b[i][j]=printRandoms(7,8);
		}
	}
	
	start = clock();
	//time count starts 
	//srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			for(int k=0;k<m;k++)
			{
				c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
			}
		}
	}
	end = clock();
	//time count stops 
	total_time_serial = ((double) (end - start)/CLOCKS_PER_SEC);
	//calulate total time
	printf("\nTotal Time Taken for serial: %f", total_time_serial);
	
	
	
	start = clock();
	//time count starts 
	//srand(time(NULL));
	#pragma omp parallel for
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				for(int k=0;k<m;k++)
				{
					c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
				}
			}
		}
		
	end = clock();
	//time count stops 
	total_time_parallel = ((double) (end - start)/CLOCKS_PER_SEC);
	//calulate total time
	printf("\nTotal Time Taken for parallel: %f", total_time_parallel);
	if(total_time_parallel < total_time_serial)
	{
		printf("\nParallel Execution is faster. Serial took %f milliseconds longer than Serial.\n",total_time_serial-total_time_parallel);
	}
	else
	{
		printf("\nSerial Execution is faster. Parallel took %f milliseconds longer than Parallel.\n",total_time_parallel-total_time_serial);
	}
	return 0;
}
