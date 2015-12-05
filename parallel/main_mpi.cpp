//#define _CRT_SECURE_NO_WARNINGS
//
//#include "mpi.h" 
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//
//
//
//int main(int argc, char *argv[])
//{ 
//	int *v1 = NULL;
//	int *v2 = NULL;
//	int size = 0;
//	int res = 0;
//	int tmp = 0;
//	double startTime, endTime, pstartTime, pendTime;
//	int procRank, procNum, n;
//	int pRes = 0;
//	
//	if (argc > 1)
//	{
//		n = atoi(argv[1]);
//		
//	}
//	else
//	{
//		n = 5;
//	}
//
//
//	MPI_Init(&argc, &argv);
//
//	
//	
//	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
//	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
//
//	if (procRank == 0)
//	{
//		v1 = new int[2 * n];
//		v2 = v1 + n;
//		
//		for (int i = 0; i < n; i ++)
//		{
//			v1[i] = rand() % 10;
//			v2[i] = rand() % 10;
//			if (n <= 10)
//				printf("%d %d \n", v1[i], v2[i]);
//
//		}
//		startTime = MPI_Wtime();
//	}
//
//	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	
//	
//	
//	if (procRank != procNum - 1)
//	{
//		size = n / (procNum);			
//	}
//	else
//	{
//		size = n / (procNum) + n % (procNum);
//	}
//
//		
//	if (procRank == 0)
//	{
//		//size = n / (procNum);
//		int i;
//		for (i = 1; i < procNum - 1; ++i)
//		{
//			MPI_Send(v1 + i * size, size, MPI_INT, i, 0, MPI_COMM_WORLD);
//			MPI_Send(v2 + i * size, size, MPI_INT, i, 0, MPI_COMM_WORLD);
//
//			
//		}
//		
//		MPI_Send(v1 + i * size, (size + n % procNum), MPI_INT, i, 0, MPI_COMM_WORLD);
//		MPI_Send(v2 + i * size, (size + n % procNum), MPI_INT, i, 0, MPI_COMM_WORLD);
//
//	}
//
//	
//	if (procRank != 0)
//	{
//		v1 = new int[2 * size];
//		v2 = v1 + size;
//
//		MPI_Recv(v1, size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//		MPI_Recv(v2, size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	}
//
//		
//	for (int i = 0; i < size ; i ++)
//	{
//			
//		tmp += v1[i] * v2[i];
//			
//	}
//	
//	
//	MPI_Reduce(&tmp, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//	
//	if (procRank == 0)
//	{
//		printf("Size of vectors: %d \n", n);
//		printf("Parallel result: %d \n", res);
//		endTime = MPI_Wtime();
//		printf("Parallel time: %lf \n", (endTime - startTime));
//		tmp = 0;
//		pstartTime = MPI_Wtime();
//		for (int i = 0; i < 2 * n; i += 2)
//		{
//			tmp += v1[i] * v1[i + 1];
//		}
//		pendTime = MPI_Wtime();
//		printf("Linear result: %d \n", res);		
//		printf("Linear time: %lf", (pendTime - pstartTime));
//
//		
//	}
//
//	MPI_Finalize(); 
//	return 0;
//
//} 