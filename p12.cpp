#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	int a[100];
	
	srand(time(NULL));
	
	for (int i = 0; i < 100; i++)
	{
		a[i] = rand() % 1000;
	}
	
	omp_set_num_threads(10);
	int max = a[0];
	#pragma omp parallel for shared(max)
	
		for (int i = 0; i < 100; i++)
		{
			#pragma omp critical
				if (a[i] % 7 == 0 && a[i] > max)
				{
					max = a[i];
				}
		}
	
	
	printf("Max = %d\n", max);
	return 0;
}
