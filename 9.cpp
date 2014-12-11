#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	int vector[500], matrix[600][500], result[600];
	int m = 600, n = 500;
	int matrixSize = 3000;
	srand(time(NULL));
	
	for (int i = 0; i < n; i++) {
		vector[i] = rand() % 10;
		for (int j = 0; j < m; j++)
		{
			matrix[j][i] = rand() % 10;
		}
	}
	
	double startTime = omp_get_wtime();
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
		for (int j = 0; j < n; j++)
		{
			result[i] += matrix[i][j] * vector[j];
		}
	}
	double endTime = omp_get_wtime();
	printf("Simple program time: %f\n", endTime - startTime);
	
	startTime = omp_get_wtime();
	omp_set_num_threads(4);
	#pragma omp parallel for
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
		for (int j = 0; j < n; j++)
		{
			result[i] += matrix[i][j] * vector[j];
		}
	}
	endTime = omp_get_wtime();
	printf("Parallel program with simple for time: %f\n", endTime - startTime);
	
	startTime = omp_get_wtime();
	#pragma omp parallel for schedule(static, 5)
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
		for (int j = 0; j < n; j++)
		{
			result[i] += matrix[i][j] * vector[j];
		}
	}
	endTime = omp_get_wtime();
	printf("Parallel program with static scheduling time: %f\n", endTime - startTime);
	
	startTime = omp_get_wtime();
	#pragma omp parallel for schedule(dynamic, 5)
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
		for (int j = 0; j < n; j++)
		{
			result[i] += matrix[i][j] * vector[j];
		}
	}
	endTime = omp_get_wtime();
	printf("Parallel program with dynamic scheduling time: %f\n", endTime - startTime);
	
	startTime = omp_get_wtime();
	#pragma omp parallel for schedule(guided, 5)
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
		for (int j = 0; j < n; j++)
		{
			result[i] += matrix[i][j] * vector[j];
		}
	}
	endTime = omp_get_wtime();
	printf("Parallel program with guided scheduling time: %f\n", endTime - startTime);
	
	startTime = omp_get_wtime();
	#pragma omp parallel for schedule(runtime)
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
		for (int j = 0; j < n; j++)
		{
			result[i] += matrix[i][j] * vector[j];
		}
	}
	endTime = omp_get_wtime();
	printf("Parallel program with runtime scheduling time: %f\n", endTime - startTime);

	return 0;
}
