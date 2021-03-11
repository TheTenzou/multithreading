// mpi_task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
	const int N = 100;
	int threads_count, thread;
	MPI_Status status;

	double s_time, e_time;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &threads_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);

	double x[N];

	if (thread == 0) {
		for (int i = 0; i < N; i++) {
			x[i] = i;
		}
		s_time = MPI_Wtime();
	}
	MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (threads_count > N) threads_count = N;

	int chunk_size = 1 + (N - 1) / threads_count;

	int s_pos = thread * chunk_size;
	int e_pos = (thread + 1) * chunk_size;
	if (e_pos > N) e_pos = N;

	double local_summ = 0;
	for (int i = s_pos; i < e_pos; i++) {
		local_summ += x[i];
	}

	double total_summ = 0;
	if (thread == 0) {
		for (int i = 1; i < threads_count; i++) {
			MPI_Recv(&local_summ, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
			std::cout << "thread: " << i << " local summ: " << local_summ << std::endl;
			total_summ += local_summ;
		}
		e_time = MPI_Wtime();
	}
	else {
		MPI_Send(&local_summ, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	if (thread == 0) {
		std::cout << "Total summ = " << total_summ << std::endl;
		std::cout << "time is " << e_time - s_time << std::endl;
	}

	MPI_Finalize();

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
