#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	int size, rank;
	omp_set_dynamic(0);
	omp_set_num_threads(8);
	
	#pragma omp parallel private (size, rank)
	{
		rank = omp_get_thread_num();
		size = omp_get_num_threads();
		
		printf("Thread number: %d; threads count: %d --- Hello, world!\n", rank, size);
	}
	return 0;
}
