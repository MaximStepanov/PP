#include <mpi.h>
#include <iostream>
#include <math.h>

double f (double x)
{
	return 4 / (1 + x * x);
}

int main (int argc, char* argv[])
{
	double a, b, ar, br, len, x0, x1, h, r, s;
	int size, rank, i;
	
	const int n = 1000;
	
	a = 0;
	b = 1;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	len = (b - a) / size;
	
	ar = a + rank * len;

	br = ar + len;
	x0 = ar;
	h = (br - ar) / n;
	
	s = 0;
	for (i = 1; i < n; i++)
	{
		x1 = x0 + h;
		s += ((f(x0) + f(x1)) / 2) * h;
		x0 = x1;
	}
	MPI_Reduce(&s, &r, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) printf("int = %f\n", r);
	MPI_Finalize();
	return 0;
}