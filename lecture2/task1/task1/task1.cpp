// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <clocale>
#include <omp.h>
#include <vector>
using namespace std;


void init_vec(vector <vector <int>>& base) {
	for (int i = 0; i < base.size(); i++)
		base[i].resize(0);
}


void static_threads(int param, vector <vector <int>>& base) {
	int i, n;
#pragma omp parallel private(i, n)
	{
		n = omp_get_thread_num();
#pragma omp for schedule(static, param)
		for (i = 1; i <= 10; i++) base[n].push_back(i);
	}
}

void dynamic_threads(int param, vector <vector <int>>& base) {
	int i, n;
#pragma omp parallel private(i, n)
	{
		n = omp_get_thread_num();
#pragma omp for schedule(dynamic, param)
		for (i = 1; i <= 10; i++) base[n].push_back(i);
	}
}

void guided_threads(int param, vector <vector <int>>& base) {
	int i, n;
#pragma omp parallel private(i, n)
	{
		n = omp_get_thread_num();
#pragma omp for schedule(guided, param)
		for (i = 1; i <= 10; i++) base[n].push_back(i);
	}
}

int main() {
	omp_set_num_threads(4);
	vector <vector <int>> base;
	base.resize(4);
	init_vec(base);

	cout << "\t" << "static" << endl;
	cout << "=======================" << endl;
	for (int k = 1; k <= 2; k++) {
		static_threads(k, base);
		cout << "param = " << k << endl;
		for (int i = 0; i < 4; i++) {
			cout << i << "|\t";
			for (int j = 0; j < base[i].size(); j++) cout << base[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		init_vec(base);
	}

	cout << "\t" << "dynamic" << endl;
	cout << "=======================" << endl;
	for (int k = 1; k <= 2; k++) {
		dynamic_threads(k, base);
		cout << "param = " << k << endl;
		for (int i = 0; i < 4; i++) {
			cout << i << "|\t";
			for (int j = 0; j < base[i].size(); j++) cout << base[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		init_vec(base);
	}

	cout << "\t" << "guided" << endl;
	cout << "=======================" << endl;
	for (int k = 1; k <= 2; k++) {
		guided_threads(k, base);
		cout << "param = " << k << endl;
		for (int i = 0; i < 4; i++) {
			cout << i << "|\t";
			for (int j = 0; j < base[i].size(); j++) cout << base[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		init_vec(base);
	}

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
