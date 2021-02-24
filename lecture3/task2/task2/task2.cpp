// task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <omp.h>

int t;

using namespace std;

double fnc(double x)
{
	if (t == 1)
	{
		return sin(x);
	}
	else if (t == 2)
	{
		return x * sin(x * x) + 1;
	}
	else if (t == 3)
	{
		return pow((x - 1), 3);
	}
	else if (t == 4)
	{
		return x*x;
	}
}

struct answer_type {
	double x;
	double y;
	double di;
};


int main()
{
	omp_set_num_threads(2);
	ofstream output;
	output.open("ans.txt");
	double x;
	double b;
	//double h = 0.01;
	const int step = 10000;
	cout << "Function #: ";
	cin >> t;
	cout << "A: ";
	cin >> x;
	cout << "B: ";
	cin >> b;
	output << "x y d_n=1 d_n=3" << endl;

	double h = abs(x - b) / step;

	answer_type answer[step];

	int i = 0;

	double t1 = omp_get_wtime();
#pragma omp parallel private(i)
	{
#pragma omp for schedule(guided, 10)
 		for (i = 0; i < step; i++)
		{
			
			double tmp = x + h*i;
			answer[i].x = tmp;
			answer[i].y = fnc(tmp);
			answer[i].di = (fnc(tmp + h) - fnc(tmp)) / h;
		}
	}
	double t2 = omp_get_wtime();
/*
	for (int i = 0; i < step; i++) 
	{
		cout << "x = " << setw(5) << setprecision(4) << answer[i].x << ' ';
		output << "x = " << setw(5) << setprecision(4) << answer[i].x << ' ';
		cout << "y = " << setw(5) << setprecision(4) << answer[i].y << ' ';
		output << "y = " << setw(5) << setprecision(4) << answer[i].y << ' ';
		cout << "y' = " << setw(5) << setprecision(4) << answer[i].di << ' ' << endl;
		output << "y' = " << setw(5) << setprecision(4)<< answer[i].di << ' ' << endl;
	}
	*/
	output.close();
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
