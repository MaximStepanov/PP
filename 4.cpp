#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int a[10] = { 5, -1, 7, 0, 14, 5, 9, 11, 18, 8 };
	int b[10] = { 7, -3, 11, 16, -5, 33, 7, 9, 10, 8 };
	
	omp_set_num_threads(2);
	
	#pragma omp parallel shared(a, b)
	{
		int rank = omp_get_thread_num();
		if (rank == 0)
		{
			int min = a[0];
			for (int i = 1; i < 10; i++)
			{
				if (a[i] < min)
				{
					min = a[i];
				}
			}
			printf ("Thread %d: minimum of array a = %d\n", rank, min);
		}
		else
		{
			int max = b[0];
			for (int i = 1; i < 10; i++)
			{
				if (b[i] > max)
				{
					max = b[i];
				}
			}
			printf("Thread %d: maximum of array b = %d\n", rank, max);
		}
	}
	return 0;
}