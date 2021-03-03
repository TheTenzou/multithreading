// Task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

using namespace std;

vector<vector<vector<vector<int>>>> algebraicComplement(vector<vector<int>> m) {
	vector<vector<vector<vector<int>>>> answer;
	answer.resize(m.size());
	for (int i = 0; i < answer.size(); i++) {
						cout << "1";
		answer[i].resize(m[i].size());
		for (int j = 0; j < answer[i].size(); j++) {
						cout << "2";
			answer[i][j].resize(m.size()-1);
			for (int k = 0; k < answer[i][j].size(); k++) {
						cout << "3";
				answer[i][j][k].resize(m[i].size()-1);
				for (int l = 0; l < answer[i][j][k].size(); l++) {	
						cout << "4";
					if ((i != k) || (l != j)) {
						int new_k = i > k ? k : k - 1;
						int new_l = l > j ? l : l - 1;
						answer[i][j][new_k][l > j ? l : l - 1] = m[k][l];
					}
				}
			}
		}
	}
	return answer;
}

int main()
{

	cout << "#" << endl;
	srand(time(0));
	int n = 3;
	int m = 3;
	vector<vector<int>> matrix(n, vector<int>(m, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i][j] = rand() % (m * n * 100);
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl << "=========================" << endl << endl;


	vector<vector<vector<vector<int>>>> answer = algebraicComplement(matrix);

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			for (int k = 0; k < matrix.size()-1; k++) {
				for (int l = 0; l < matrix[i].size()-1; l++) {	
					cout << answer[i][j][k][l] << " ";
				}
				cout << endl;
			}
			cout << endl << endl << "================" << endl;
		}
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
