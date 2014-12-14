#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char * argv[])
{
	int a[5][5];
	int n = 5, m = 5, result, max, locMin;
	int size, rank;
	int count = 0;
	srand(time(NULL));
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			a[i][j] = rand() % 10;
		}
	}
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0)
	{
		printf("Array a:\n");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}
	}
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	

	for (int i = rank; i < n; i += size)
	{
		locMin = a[i][0];
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] < locMin)
			{
				locMin = a[i][j];
			}
		}
		if (i == rank)
		{
			max = locMin;
		}
		if (locMin > max)
		{
			max = locMin;
		}
		
	}
	
	MPI_Reduce(&max, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
	if (rank == 0)
	{
		printf("Result is %d\n", result);
	}
	MPI_Finalize();
	return 0;
}
