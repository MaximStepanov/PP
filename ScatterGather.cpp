#include <iostream>
#include <mpi.h>

using namespace std;
 
int main(int argc, char *argv[]) {
        int rank, size, *recv;
 
        int arr[] = {1, 2, 3, 4, 10, 6, 7, 8, 9};
        int n = sizeof(arr) / sizeof(int);
 
        if (n > 0) {
                MPI_Status status;
 
                MPI_Init(&argc, &argv);
                MPI_Comm_size(MPI_COMM_WORLD, &size);
                MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
                if (rank == 0) {
                        for (int i = 1; i < size; i++) {
                                int start = i * n / size;
                                int end = (i + 1) * n / size;
                                MPI_Send(&arr[start], end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
                        }
                }
               
                int start = rank * n / size;
                int end = (rank + 1) * n / size;
                int m = end - start;
 
                recv = new int[m];
 
                if (rank != 0) {
                        MPI_Recv(recv, m, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                        for(int i=0;i<m;i++)
                        MPI_Send(recv, m, MPI_INT, 0, 1, MPI_COMM_WORLD);
                }
 
                if (rank == 0) {
                        int *r = new int[n];
                        for (int i = 1; i < size; i++) {
                                int startr = i * n / size;
                                int endr = (i+1) * n / size;
                                MPI_Recv(&r[startr], endr-startr, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
                        }
                        for (int j = 0; j < n / size; j++) {
                                r[j] = arr[j];
                        }
                        for (int i = 0; i < n; i++) {
                                cout<<r[i]<<" ";
                        }
                        cout<<endl;
                }
 
                MPI_Finalize();
        }
       
}