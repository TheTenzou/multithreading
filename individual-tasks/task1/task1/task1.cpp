// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <fstream>

using namespace std;

vector<double> solve(vector<vector<double>> m, vector<double> x, vector<double> b) {
	vector<double> ans(x.size(), 0);
	for (int i = 0; i < m.size(); i++) {
		ans[i] = b[i];
		for (int j = 0; j < m[i].size(); j++) {
			if (i != j) {
				ans[i] -= m[i][j] * x[j];
			}
		}
		ans[i] /= m[i][i];
	}
	return ans;  
}

vector<double> diff_vec(vector<double> a, vector<double> b) {
	vector<double> c(a.size(), 0);
	for (int i = 0; i < a.size(); i++) {
		c[i] = a[i] - b[i];
	}
	return c;
}

double norma(vector<double> a) {
	double max = a[0];
	for (int i = 1; i < a.size(); i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;
}
/*
int main()
{
	cout << "Enter file name: " << endl;
	string fileName;
	cin >> fileName;
	ifstream file;
	file.open(fileName + ".txt");

	int n;
	file >> n;

	vector<vector<double>> matrix;
	vector<double> b(n, 0);
	matrix.resize(n);
	for (int i = 0; i < n; i++) {
		matrix[i].resize(n);
		for (int j = 0; j < n; j++) {
			file >> matrix[i][j];
		}
		file >> b[i];
	}
	
	vector<double> x1(n, 0), x2 = solve(matrix, x1, b), x0;

	while (abs(norma(diff_vec(x2, x1))) > 0.00001) {
		x1 = x2;
		x2 = solve(matrix, x2, b);
		cout << "=========================================" << endl;
		for (int i = 0; i < n; i++) {
			cout << x2[i] << " ";
		}
		cout << endl;
	}

	cout << "=========================================" << endl;
	for (int i = 0; i < n; i++) {
		cout << x2[i] << " ";
	}
}
*/
int main()
{
	cout << "Enter file name: " << endl;
	string fileName;
	cin >> fileName;
	ifstream file;
	file.open(fileName + ".txt");

    int size;
    file >> size;

    vector <vector <long double> > matrix;

    matrix.resize(size);
    for (int i = 0; i < size; i++)
    {
        matrix[i].resize(size + 1);

        for (int j = 0; j < size + 1; j++)
        {
            file >> matrix[i][j];
        }
    }
	cout << size << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size + 1; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

    long double eps;
    cin >> eps;

    vector <long double> previousVariableValues(size, 0.0);

    while (true)
    {
        vector <long double> currentVariableValues(size);


        for (int i = 0; i < size; i++)
        {
            currentVariableValues[i] = matrix[i][size];

            for (int j = 0; j < size; j++)
            {
                if (i != j)
                {
                    currentVariableValues[i] -= matrix[i][j] * previousVariableValues[j];
                }
            }

            currentVariableValues[i] /= matrix[i][i];
        }

        long double error = 0.0;

        for (int i = 0; i < size; i++)
        {
            error += abs(currentVariableValues[i] - previousVariableValues[i]);
        }

        if (error < eps)
        {
            break;
        }

        previousVariableValues = currentVariableValues;

		for (int i = 0; i < size; i++) {
			cout << currentVariableValues[i] << " ";
		}
		cout << endl;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%.8llf ", previousVariableValues[i]);
    }
	
	file.close();

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
