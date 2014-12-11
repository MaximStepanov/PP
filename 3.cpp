#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char * argv[])
{
	int a = 10, b = 12;
	
	
	omp_set_num_threads(2);
	printf ("Before first area: a = %d, b = %d\n", a, b);
	#pragma omp parallel private(a) firstprivate(b)
	{
		int rank = omp_get_thread_num();
		printf("First area, thread number: %d\n",rank);
		a = a + rank;
		b = b + rank;
		printf ("Inside first area: a = %d, b = %d\n", a, b);
	}
	printf ("After first area: a = %d, b = %d\n", a, b);
	
	
	printf ("Before second area: a = %d, b = %d\n", a, b);
	omp_set_num_threads(4);
	#pragma omp parallel shared(a) private(b)
	{
		int rank = omp_get_thread_num();
		printf ("Second area, thread number: %d\n", rank);
		a = a - rank;
		b = b - rank;
		printf ("Inside second area: a = %d, b = %d\n", a, b);
	}
	printf ("After second area: a = %d, b = %d\n", a, b);
	return 0;
}