#include <mpi.h>
#include <iostream>

using namespace std;
int main(int argc, char* argv[])
{
	int size, rank, RecvRank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		cout<<"Hello from process_"<<rank<<endl;
		for (int i = 0; i < size; i++)
		{
			MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout<<"Hello from process "<<RecvRank<<endl;
		}
	} else
	{
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Finalize();
	}
	return 0;
}
