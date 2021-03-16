// mpi_task4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
	const int N = 100, M = 100;

	int chunk, thread_count, thread, s_pos, e_pos;

	double totalMax = 0;
	double max = 0;
	double s_time, e_time;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);

	std::cout << "Process " << thread << " of " << thread_count << " started\n";

	double x[N][M];

	if (thread == 0) {
		
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < M; j++) 
				x[i][j] =  (i + j);

		s_time = MPI_Wtime();
	}

	if (thread_count > N) thread_count = N;

	MPI_Bcast(x, N * M, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	chunk = N / thread_count;
	s_pos = chunk * thread;
	e_pos = chunk * (thread + 1);
	if (e_pos > N) e_pos = N;

	for (int i = s_pos; i < e_pos; i++)
		for (int j = 0; j < M; j++)
			if (abs(x[i][j]) > max)
				max = abs(x[i][j]);
	if (thread == 0) {
		std::cout << "Max of process number 0 = " << max << "\n";
		totalMax = max;

		for (int i = 1; i < thread_count; i++) {
			MPI_Recv(&max, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
			
			std::cout << "Max of process number " << i << " = " << max << "\n";
			totalMax = std::max(totalMax, max);
		}

		e_time = MPI_Wtime();
	} else {
		MPI_Send(&max, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	if (thread == 0) {
		std::cout << "max is " << totalMax << "\n";
		std::cout << "time is " << e_time - s_time << "\n";
	}

	MPI_Finalize();
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
