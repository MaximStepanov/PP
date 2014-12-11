#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int size, rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int x = 0;
	if (rank == 0) {
		MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&x, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
	}
	else 
		if (rank == size - 1) {
			MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
			x++;	
			MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);		
		}
		else {
			MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);			
			x++;	
			MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		}
	if(rank == 0)
		printf("Value x = %d\n", x);	
	MPI_Finalize();
}