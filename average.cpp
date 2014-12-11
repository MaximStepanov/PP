#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int size, rank, locSum, locCount, sum, count; 
	int n = 10;
	int a[10] = { -1, 4, 0, -3, 5, 3, -5, 2, 1, 8 };
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	locSum = 0;
	locCount = 0;
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = rank; i < n; i += size)
	{
		if (a[i] > 0)
		{
			locSum += a[i];
			locCount++;
		}
	}
	MPI_Reduce(&locSum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&locCount, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (rank == 0)
	{
		printf("Average = %f\n", sum / (count * 1.0));
	}
	
	MPI_Finalize();
	return 0;
}