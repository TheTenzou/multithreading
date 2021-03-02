// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <fstream>

using namespace std;

int chank_size = 4;


vector<double> solve_static(vector<vector<double>> m, vector<double> x, vector<double> b) {
    vector<double> ans(x.size(), 0);

#pragma omp parallel
    {
#pragma omp for schedule(static, chank_size)
        for (int i = 0; i < m.size(); i++) {
            ans[i] = b[i];
            for (int j = 0; j < m[i].size(); j++) {
                if (i != j) {
                    ans[i] -= m[i][j] * x[j];
                }
            }
            ans[i] /= m[i][i];
        }
    }
    return ans;  
}

vector<double> diff_vec_static(vector<double> a, vector<double> b) {
    vector<double> c(a.size(), 0);
#pragma omp parallel
	{
#pragma omp for schedule(static, chank_size)
		for (int i = 0; i < a.size(); i++) {
			c[i] = a[i] - b[i];
		}
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


vector<double> solve_dynamic(vector<vector<double>> m, vector<double> x, vector<double> b) {
    vector<double> ans(x.size(), 0);

#pragma omp parallel
    {
#pragma omp for schedule(dynamic, chank_size)
        for (int i = 0; i < m.size(); i++) {
            ans[i] = b[i];
            for (int j = 0; j < m[i].size(); j++) {
                if (i != j) {
                    ans[i] -= m[i][j] * x[j];
                }
            }
            ans[i] /= m[i][i];
        }
    }
    return ans;  
}

vector<double> diff_vec_dynamic(vector<double> a, vector<double> b) {
    vector<double> c(a.size(), 0);
#pragma omp parallel
	{
#pragma omp for schedule(dynamic, chank_size)
		for (int i = 0; i < a.size(); i++) {
			c[i] = a[i] - b[i];
		}
	}
    return c;
}

vector<double> solve_guided(vector<vector<double>> m, vector<double> x, vector<double> b) {
    vector<double> ans(x.size(), 0);

#pragma omp parallel
    {
#pragma omp for schedule(guided, chank_size)
        for (int i = 0; i < m.size(); i++) {
            ans[i] = b[i];
            for (int j = 0; j < m[i].size(); j++) {
                if (i != j) {
                    ans[i] -= m[i][j] * x[j];
                }
            }
            ans[i] /= m[i][i];
        }
    }
    return ans;  
}

vector<double> diff_vec_guided(vector<double> a, vector<double> b) {
    vector<double> c(a.size(), 0);
#pragma omp parallel
	{
#pragma omp for schedule(guided, chank_size)
		for (int i = 0; i < a.size(); i++) {
			c[i] = a[i] - b[i];
		}
	}
    return c;
}

int main()
{
    /*
    cout << "Enter file name: " << endl;
    string fileName;
    cin >> fileName;
    ifstream file;
    file.open(fileName + ".txt");

    int n;
    file >> n;
    */
	
	ofstream file;
	file.open("static.txt");

	file << "static" << endl;
	file << "threads, \"chank size\", time " << endl;

	for (int i = 2; i <= 4; i++) {
		omp_set_num_threads(i);
		for (chank_size = 100; chank_size >= 10; chank_size -= 10) {
			int n = 3000;
			vector<vector<double>> matrix;
			vector<double> b(n, 0);
			matrix.resize(n);
			for (int i = 0; i < n; i++) {
				matrix[i].resize(n);
				for (int j = 0; j < n; j++) {
					//file >> matrix[i][j];
					if (i == j) {
						matrix[i][j] = (double)i + j + 1;
						matrix[i][j] *= n;
					}
					else {
						matrix[i][j] = 1;
					}
				}
				//file >> b[i];
				b[i] = i;
			}

			double time_start = omp_get_wtime();

			vector<double> x1(n, 0), x2 = solve_static(matrix, x1, b), x0;

			while (abs(norma(diff_vec_static(x2, x1))) > 0.00001) {
				x1 = x2;
				x2 = solve_static(matrix, x2, b);
			}

			double time_end = omp_get_wtime();

			//for (int i = 0; i < n; i++) {
			//	cout << x2[i] << " ";
			//}

			file << i << ", " << chank_size << ", " << time_end - time_start << endl;
		}
	}


	file << "dyanmic" << endl;
	file << "threads, \"chank size\", time " << endl;

	for (int i = 2; i <= 4; i++) {
		omp_set_num_threads(i);
		for (chank_size = 100; chank_size >= 10; chank_size -= 10) {
			int n = 3000;
			vector<vector<double>> matrix;
			vector<double> b(n, 0);
			matrix.resize(n);
			for (int i = 0; i < n; i++) {
				matrix[i].resize(n);
				for (int j = 0; j < n; j++) {
					//file >> matrix[i][j];
					if (i == j) {
						matrix[i][j] = (double)i + j + 1;
						matrix[i][j] *= n;
					}
					else {
						matrix[i][j] = 1;
					}
				}
				//file >> b[i];
				b[i] = i;
			}

			double time_start = omp_get_wtime();

			vector<double> x1(n, 0), x2 = solve_dynamic(matrix, x1, b), x0;

			while (abs(norma(diff_vec_dynamic(x2, x1))) > 0.00001) {
				x1 = x2;
				x2 = solve_dynamic(matrix, x2, b);
			}

			double time_end = omp_get_wtime();

			//for (int i = 0; i < n; i++) {
			//	cout << x2[i] << " ";
			//}

			file << i << ", " << chank_size << ", " << time_end - time_start << endl;
		}
	}

	file << "guided" << endl;
	file << "threads, \"chank size\", time " << endl;

	for (int i = 2; i <= 4; i++) {
		omp_set_num_threads(i);
		for (chank_size = 100; chank_size >= 10; chank_size -= 10) {
			int n = 3000;
			vector<vector<double>> matrix;
			vector<double> b(n, 0);
			matrix.resize(n);
			for (int i = 0; i < n; i++) {
				matrix[i].resize(n);
				for (int j = 0; j < n; j++) {
					//file >> matrix[i][j];
					if (i == j) {
						matrix[i][j] = (double)i + j + 1;
						matrix[i][j] *= n;
					}
					else {
						matrix[i][j] = 1;
					}
				}
				//file >> b[i];
				b[i] = i;
			}

			double time_start = omp_get_wtime();

			vector<double> x1(n, 0), x2 = solve_guided(matrix, x1, b), x0;

			while (abs(norma(diff_vec_guided(x2, x1))) > 0.00001) {
				x1 = x2;
				x2 = solve_guided(matrix, x2, b);
			}

			double time_end = omp_get_wtime();

			//for (int i = 0; i < n; i++) {
			//	cout << x2[i] << " ";
			//}

			file << i << ", " << chank_size << ", " << time_end - time_start << endl;
		}
	}
	file.close();
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
