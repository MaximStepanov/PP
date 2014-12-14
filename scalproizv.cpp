#include <mpi.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define TAG 1

using namespace std;

int main (int argc, char * argv[]) 
{
	int rank, size, total, n, dest;
	int *a, *b, sum, result;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) 
	{
 	cout << "Введите длину векторов" << endl;
	cin >> total;
	n = total / size + 1;
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	a = (int*) malloc(n * sizeof(int));
	b = (int*) malloc(n * sizeof(int));
	
	if (a == NULL || b == NULL)
	{
		cout << "Недостаточно памяти" << endl;
		exit(1);
	}
	if (rank == 0)
	{
		for (dest = 1; dest < size; dest++)
		{
			for (int i = 0; i < n; i++)
			{
				a[i] = rand();
				b[i] = rand();
			}
			MPI_Send(a, n, MPI_INT, dest, TAG, MPI_COMM_WORLD);
			MPI_Send(b, n, MPI_INT, dest, TAG, MPI_COMM_WORLD);
			n = total - n * (size - 1);
			for (int i = 0; i < n; i++)
			{
				a[i] = rand();
				b[i] = rand();
			}
		} 
	}
	else
	{
		MPI_Recv(a, n, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(b, n, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);
	}
	sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i] * b[i];
	}
	
	MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		cout << "Скалярное произведение равно " << result << endl;
	}
	
	MPI_Finalize();
	return 0;
	
}
