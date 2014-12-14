#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define MYTAG 1
 
int main(int argc, char *argv[])
{
	int n, size, i, dest, rank;
    int a[10], arr[10];;
    MPI_Status status;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		n = 10 / size;
	}
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
    if (rank == 0) 
	{
		for (dest = 1; dest < size; dest++) 
		{
        	for (i = 0; i < n; i++) 
			{
            	a[i] = dest*(i + 1);
				printf("%d ", a[i]);
                
			}
			MPI_Send(a, n, MPI_INT, dest, MYTAG, MPI_COMM_WORLD);
			
        }
		n = 10 - n * (size - 1);
		for (i = 0; i < n; i++)
		{
			a[i] = i - 1;
			printf("%d ", a[i]);
		}
	} 
	else 
	{
		MPI_Recv(a, n, MPI_INT, 0, MYTAG, MPI_COMM_WORLD, &status);
	}
 
    int temp;
    for (i = 0; i < n / 2; i++) 
	{
        temp = a[n - i - 1];
        a[n - i - 1] = a[i];
        a[i] = temp;
    }
	MPI_Gather(a, n, MPI_INT, arr, n, MPI_INT, 0, MPI_COMM_WORLD);
	
 	if (rank == 0) {
		printf("\n");
    	for(i = 0; i < 10; i++) 
		{
        	printf("a[%d] = %d \n", i, arr[i]);
        }         
	}
 
    MPI_Finalize();
    return 0;
}
