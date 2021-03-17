// mpi_task5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int thread_count, thread, next, prev, buf[2], tag1 = 1, tag2 = 2;
	double s_time, e_time;

	MPI_Request reqs[4];
	MPI_Status status[4];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);

	s_time = MPI_Wtime();

	prev = thread - 1;
	next = thread + 1;

	if (thread == 0) prev = thread_count - 1;
	if (thread == (thread_count - 1)) next = 0;

	MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);

	MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);

	MPI_Isend(&thread, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
	std::cout << "Precess number: " << thread << " send message " << thread << " to process number " << prev << "\n";

	MPI_Isend(&thread, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);
	std::cout << "Precess number: " << thread << " send message " << thread << " to process number " << next << "\n";

	MPI_Waitall(4, reqs, status);
	
	std::cout << "Process number: " << thread << " recieve message " << buf[0] << " from process number " << prev << "\n";

	std::cout << "Process number: " << thread << " recieve message " << buf[1] << " from process number " << next << "\n";

	std::cout << "Node " << thread << " : ok!\n";

	e_time = MPI_Wtime();
	std::cout << "Time of proces number " << thread << " is: " << e_time - s_time << "\n";

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
