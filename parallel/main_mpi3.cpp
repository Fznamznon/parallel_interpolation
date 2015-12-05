#define _USE_MATH_DEFINES

#include <mpi.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>



using namespace std;

double testf(double x)
{
	return x * x;
}

const int cnt = 10;

int main(int argc, char *argv[])
{

	int n; // число узлов интерпол€ции
	int size;
	int a = -1;
	int b = 1;
	
	
	double l_val[cnt] = { 0 };
	

	if (argc > 1)
	{
		n = atoi(argv[1]);
	}
	else
	{
		n = 4;
	}

	double *X = new double[n]; //узлы интерпол€ции
	double *Y = new double[n];

	int procNum, procRank;
	
	MPI_Init(&argc, &argv);


			
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

	size = n / procNum;
	
	if (procRank == 0)
	{
		for (int i = 0; i < n; ++i)
		{
			X[i] = 0.5 * (a + b) + 0.5 * (b - a) * cos(M_PI*(2 * i + 1) / (2 * n * 1.0));
			Y[i] = testf(X[i]);
			//printf_s("X[i] = %lf \n", X[i]);
			//printf_s("Y[i] = %lf \n", Y[i]);

		}

		
		
	}
	MPI_Bcast(X, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(Y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	

	double basics_pol = 1;
	double small_pol = 0;
	for (int k = 0; k < cnt; ++k)
	{
		
		small_pol = 0;
		for (int i = procRank * size; i < (procRank + 1) * size + ((procRank == procNum - 1)? n % procNum: 0); ++i)
		{
			basics_pol = 1.0;
			for (int j = 0; j < n; ++j)
			{
				
				if (j == i) continue;
				
				basics_pol *= ((k+1) - X[j]) / (X[i] - X[j]);
				
			}
			
			small_pol += basics_pol * Y[i];
			
		}
		

		MPI_Reduce(&small_pol, &l_val[k], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		

	}

	if (procRank == 0)
	{
		for (int i = 0; i < cnt; ++i)
		{
			printf_s("x = %d : l(x) = %.15lf;  f(x) = %.7lf; \n", (i + 1), l_val[i], testf(i + 1));
		}
	}
	
	MPI_Finalize();

	return 0;
}