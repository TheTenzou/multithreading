// Task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <ctime>
#include <vector>

using namespace std;

int main()
{
	srand(time(0));
	int n = 10;
	vector<vector<int>> matrix(n, vector<int>(n, 0));

	vector<int> rows_sum(n, 0);
	vector<int> colomn_sum(n, 0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 10;
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << "======" << endl << endl;


#pragma omp parallel for schedule(guided)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			rows_sum[i] += matrix[i][j];
			colomn_sum[j] += matrix[i][j];
		}
	}

	vector<int> answare(n, 0);

#pragma omp parallel for schedule(guided)
	for (int i = 0; i < n; i++) {
			answare[i] = rows_sum[i] * colomn_sum[i];
	}

	for (int i = 0; i < n; i++) {
		cout << answare[i] << " ";
	}
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
