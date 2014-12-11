#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	srand(time(NULL));
	int a[30];
	for (int i = 0; i < 30; i++)
		a[i] = rand() % 100;
	
	int count = 0;
	
	omp_set_num_threads(5);
	
	#pragma omp parallel for
	for (int i = 0; i < 30; i++) {
		
		if (a[i] % 9 == 0)
		{
			#pragma omp atomic
			count++;
		}
	}
	printf("Count = %d\n", count);
	return 0;
}