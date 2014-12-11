#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void test (int count)
{
	#pragma omp parallel if (count)
	{
		if (omp_in_parallel())
		{
			printf ("Perfrom parallel, count = %d\n", count);
		}
		else
		{
			printf ("Perform single, count = %d\n", count);
		}
	}
}

int main (int argc, char * argv[])
{
	int size, rank;
	
	omp_set_dynamic(0);
	omp_set_num_threads(3);
	
	#pragma omp parallel private(size, rank)
	{
		size = omp_get_num_threads();
		rank = omp_get_thread_num();
		printf ("Threads count: %d; number of thread: %d\n", size, rank);
		test(size);
	}
	omp_set_num_threads(1);
	#pragma omp parallel private(size, rank)
	{
		size = omp_get_num_threads();
		rank = omp_get_thread_num();
		printf ("Threads count: %d; number of thread: %d\n", size, rank);
		test(size);
	}
	return 0;
}
