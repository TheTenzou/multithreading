// mpi_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>
#include <vector>
#include <ctime>

int main(int argc, char** argv)
{
	srand(time(0));
	std::vector<int> vec;

	vec.resize(95);

	int vec_size = vec.size();

	for (int i = 0; i < vec_size; i++) {
		vec[i] = i;
	}

	int commsize;
	int rank;

	MPI_Init(&argc, &argv);
	double time1 = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);

	int chunk = 1 + (vec_size - 1) / commsize;	

	//printf("Hello, I’m processor No_%d from %d \n", rank, commsize);

	printf("Thread %d elements:", rank);
	for (int i = rank * chunk; (i < (rank + 1) * chunk) && (i < vec_size); i++) {
		printf(" %d,", vec[i]);
	}
	double time2 = MPI_Wtime();
	MPI_Finalize();
	printf("\ntime: %f", time2 - time1);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
