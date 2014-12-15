#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	int d[6][8];
	srand(time(NULL));
	
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 8; j++)
			d[i][j] = rand() % 100;
		
	omp_set_num_threads(10);
	int min = d[0][0], max = d[0][0];
	
	#pragma omp parallel for
	for (int i = 0; i < 6; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			if (d[i][j] < min)
			{
				#pragma omp critical
					if (d[i][j] < min)
					{
						min = d[i][j];
					}
			}
			if (d[i][j] > max)
			{
				#pragma omp critical
					if (d[i][j] > max)
					{
						max = d[i][j];
					}
			}
			
		}
			
	}
	printf("Min = %d; max = %d\n", min, max);
		
	return 0;
}
