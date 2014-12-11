#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int size, rank;
	int n = 10;
	int arr[10] = {7, -3, 1, 0, 6, 7, 4, 8, 15, 9};
	int locMax, max, len;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank < n) {
		locMax = arr[rank];
	}
	else
	{
		locMax = arr[9];
	}
	for (int i = rank; i < n; i += size) {
		if (arr[i] > locMax)
			locMax = arr[i];
	}
	MPI_Reduce(&locMax, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0)
		cout << "Max = " << max << endl;
	MPI_Finalize();
	return 0;
}