#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	int a[10], b[10];
	
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 10 + i;
		b[i] = rand() % 10 - i;
	}
	
	int sum = 0;
	
	#pragma omp parallel for
	
		for (int i = 0; i < 10; i++)
		{
			sum += a[i];
		}
		 
	
	printf("Average of array a is %f\n", sum / (10 * 1.0));
	
	sum = 0;
	
	#pragma omp parallel for reduction(+:sum)
	
		for (int i = 0; i < 10; i++)
		{
			sum += b[i];
		}
	
	printf("Average of array b is %f\n", sum / (10 * 1.0));
	
	return 0;
}