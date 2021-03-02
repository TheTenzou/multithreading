// task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <clocale>
#include <omp.h>
using namespace std;


int main() {
	int A[1000], B[1000], C[1000];
	omp_set_num_threads(4);
	for (int i = 0; i < 1000; i++)
	{
		A[i] = i; B[i] = 2 * i;
	}
	double t1 = omp_get_wtime();
	int n, i;
#pragma omp parallel private(i,n) 
	{
		n = omp_get_thread_num();
		cout << "Нить " << n << " начала работу " << endl;
#pragma omp for schedule(static, 2)
		for (i = 0; i < 1000; i++)
		{
			C[i] = A[i] + B[i];
		}
		cout << "Нить " << n << " закончила работу " << endl;
	}
	double t2 = omp_get_wtime();
	cout << t2 - t1 << endl;
	system("pause");
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
