// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

using namespace std;

int main()
{
	srand(time(0));
	int n = 10;
	int m = 20;
	vector<vector<int>> matrix(n, vector<int>(m, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i][j] = rand() % (m * n * 100);
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << "======" << endl << endl;

	int max_val = matrix[0][0];
	int min_val = matrix[0][0];
#pragma omp parallel for schedule(guided, 2) 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrix[i][j] > max_val) {
#pragma omp critical
				max_val = matrix[i][j];; 
			}
			if (matrix[i][j] < min_val) {
#pragma omp critical
				min_val = matrix[i][j];; 
			}
		}
	}
	cout << endl << max_val << endl;
	cout <<  min_val << endl;
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
