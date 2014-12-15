#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a[16000], b[16000];
	
	for (int i = 0; i < 16000; i++)
	{
		a[i] = i + 1;
	}
	
	omp_set_num_threads(8);
	
	printf("Static scheduling beginning...\n");
	#pragma omp parallel for schedule(static, 4)
		for (int i = 1; i < 15999; i++)
		{
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	printf("Staic scheduling has ended\n");
	
	printf("Dynamic scheduling beginning...\n");
	#pragma omp parallel for schedule(dynamic, 4)
		for (int i = 1; i < 15999; i++)
		{
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	printf("Dynamic scheduling has ended\n");
	
	printf("Guided scheduling beginning...\n");
	#pragma omp parallel for schedule(guided, 4)
		for (int i = 1; i < 15999; i++)
		{
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	printf("Guided scheduling has ended\n");
	
	
	printf("Runtime scheduling beginning...\n");
	#pragma omp parallel for schedule(dynamic, 4)
		for (int i = 1; i < 15999; i++)
		{
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	printf("Runtime scheduling has ended\n");
	return 0;
}
