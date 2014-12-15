#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int a[6][8];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			a[i][j] = rand();
		}
	}
	
	#pragma omp parallel sections private(a)
	{
		#pragma omp section
		{
			double average = 0.0;
			int sum = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sum += a[i][j];
				}
			}
			average = sum / (6 * 8);
			printf("Section 1: thread number %d; average = %f\n", omp_get_thread_num(), average);
		}
		
		#pragma omp section
		{
			int min = a[0][0];
			int max = min;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (a[i][j] > max)
						max = a[i][j];
					if (a[i][j] < min)
						min = a[i][j];
				}
			}
			printf("Section 2: thread number %d; minimum = %d, maximum = %d\n", omp_get_thread_num(), min, max);
		}
		
		#pragma omp section
		{
			int count = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (a[i][j] % 3 == 0)
					{
						count++;
					}
				}
			}
			printf("Section 3: thread number %d; count elements divided by 3: %d\n", omp_get_thread_num(), count);
		}
	}
	return 0;
}
