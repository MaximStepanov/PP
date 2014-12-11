#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	int a[12], b[12], c[12];
	srand(time(NULL));
	
	omp_set_num_threads(3);
	
	#pragma omp parallel for schedule(static, 3)
	
		for (int i = 0; i < 12; i++)
		{
			a[i] = rand() % 100 + i;
			b[i] = rand() % 100 - i;
			
			printf("First area --- threads count: %d; thread number: %d\n", omp_get_num_threads(), omp_get_thread_num());
		}
		
	for (int i = 0; i < 12; i++)
	{
		printf("First area --- a[%d] = %d; b[%d] = %d\n", i, a[i], i, b[i]);
	}
	
	
	omp_set_num_threads(4);
	
	#pragma omp parallel for schedule(dynamic, 3)
	
		for (int i = 0; i < 12; i++)
		{
			c[i] = a[i] + b[i];
			printf("Second area --- threads count: %d; thread number: %d\n", omp_get_num_threads(), omp_get_thread_num()); 
		}
		
	for (int i = 0; i < 12; i++)
	{
		printf("Second area --- c[%d] = %d\n", i, c[i]);
	}
	
	return 0;
}