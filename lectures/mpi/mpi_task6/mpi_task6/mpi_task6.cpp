// mpi_task6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int thread_count, thread, next, prev, tag1 = 1, tag2 = 2;
	int n = 100;
	int buf[100];
	int sbuf[100];

	double s_time, e_time;
	int procsum = 0, totalsum = 0, kol = 0;
	int* x;
	x = new int[n];
	for (int i = 0; i < n; i++)
		x[i] = i;

	MPI_Request reqs[2];
	MPI_Status stats[2];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);

	s_time = MPI_Wtime();

	prev = thread - 1;
	next = thread + 1;

	if (thread == 0) prev = thread_count - 1;
	if (thread == (thread_count - 1)) next = 0;

	int chunk = n / thread_count;
	int s_pos = thread * chunk;
	int e_pos = (thread + 1) * chunk;
	if (thread == thread_count - 1) e_pos = n;

	MPI_Isend(&procsum, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[0]);
	std::cout << "Pocess number: " << thread << " send message " << procsum << " to process number " << next << "\n";

	MPI_Irecv(&sbuf[thread], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[1]);

	MPI_Waitall(2, reqs, stats);

	std::cout << "Process number: " << thread << " recieve message " << sbuf[thread] << " from process number " << prev << "\n";

	e_time = MPI_Wtime();

	std::cout << "Time of process number " << thread << " is: " << e_time - s_time << "\n";

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
