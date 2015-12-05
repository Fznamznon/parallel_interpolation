//#include <mpi.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//#define n 100
//
//int _to(int r, int root, int procNum)
//{
//	return ((r - root) + procNum) % procNum + 1;
//}
//
//int _from(int r, int root, int procNum)
//{
//	return (r - 1 + root) % procNum;
//}
//
//
//void my_MPI_TREE_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
//{
//	int procNum, procRank;
//	MPI_Comm_size(comm, &procNum);
//	MPI_Comm_rank(comm, &procRank);
//
//	int _r = _to(procRank, root, procNum);
//	
//	if (procRank != root)
//		MPI_Recv(buffer, count, datatype, _from(_r / 2, root, procNum), 0, comm, MPI_STATUS_IGNORE);
//
//	if (2 * _r <= procNum)
//	{
//		MPI_Send(buffer, count, datatype, _from(2 * _r, root, procNum), 0, comm);
//	}
//	
//	if (2 * _r + 1 <= procNum)
//	{
//		MPI_Send(buffer, count, datatype, _from(2 * _r + 1, root, procNum), 0, comm);
//	}
//
//}
//
//
//
//
//void my_MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
//{
//	int procNum, procRank;
//	MPI_Comm_size(comm, &procNum);
//	MPI_Comm_rank(comm, &procRank);
//
//	if (procRank == root)
//	{
//		for (int i = 0; i < procNum; ++i)
//		{
//			if (i == root) continue;
//			MPI_Send(buffer, count, datatype, i, 0, comm);
//			
//		}
//	}
//	if (procRank != root)
//	{
//		
//		MPI_Recv(buffer, count, datatype, root, 0, comm, MPI_STATUS_IGNORE);
//		
//	}
//
//}
//
//int main(int argc, char *argv[])
//{
//	int procNum, procRank;
//	int* buffer = new int[n];
//	double tt1 = 0, lt1, tt2, lt2;
//	
//	int root;
//	if (argc > 1)
//	{
//		root = atoi(argv[1]);
//			
//	}
//	else
//	{
//		root = 0;
//	}
//
//
//	MPI_Init(&argc, &argv);
//		
//	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
//	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
//
//	if (procRank == root)
//	{
//		printf("I'am root: %d \n", root);
//		//buffer = new int[n];
//		for (int i = 0; i < n; i++)
//		{
//			buffer[i] = rand() % 10;
//			if (n <= 10)
//				printf("%d ", buffer[i]);
//		}
//		printf("\n");
//
//	}
//
//	if (procRank == root)
//		tt1 = MPI_Wtime();
//	my_MPI_TREE_Bcast(buffer, n, MPI_INT, root, MPI_COMM_WORLD);
//	if (procRank == root)
//		tt2 = MPI_Wtime();
//
//
//	if (procRank == root)
//		lt1 = MPI_Wtime();
//	my_MPI_Bcast(buffer, n, MPI_INT, root, MPI_COMM_WORLD);
//	if (procRank == root)
//		lt2 = MPI_Wtime();
//
//	if (procRank != root)
//	{
//		if (n <= 10)
//		{
//			printf("I'am proc: %d \n", procRank);
//			for (int i = 0; i < n; ++i)
//			{
//				printf("%d ", buffer[i]);
//
//			}
//			printf("\n");
//
//		}
//
//	}
//	if (procRank == root)
//	{
//		printf("flat time: %lf \n", lt2 - lt1);
//		printf("binary tree time: %lf \n", tt2 - tt1);
//	}
//	
//	MPI_Finalize();
//	return 0;
//}
