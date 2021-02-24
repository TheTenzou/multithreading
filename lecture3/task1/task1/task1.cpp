// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <clocale>
#include <omp.h>
#include <vector>
#include <ctime>
using namespace std;


int main() {
	//vector<vector<int>> a, b, c;
	const int matrix_size = 100;
	int a[matrix_size][matrix_size], b[matrix_size][matrix_size], c[matrix_size][matrix_size];

	omp_set_num_threads(8);
	//a.resize(matrix_size, vector<int>(matrix_size, 0));
	//b.resize(matrix_size, vector<int>(matrix_size, 0));
	//c.resize(matrix_size, vector<int>(matrix_size, 0));

	srand(time(0));
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			a[i][j] = rand() % 100;
			b[i][j] = rand() % 100;
		}
	}

	double t1 = omp_get_wtime();
	int n, i, j;

#pragma omp parallel 
	{
		n = omp_get_thread_num();
		//cout << "Thread " << n << " start working " << endl;

	#pragma omp for schedule(guided, 10)
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				for (int k = 0; k < matrix_size; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		//cout << "Thread " << n << " finished working " << endl;
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
