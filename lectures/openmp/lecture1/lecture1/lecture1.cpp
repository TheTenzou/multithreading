// lecture1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    cout << "Hello World!\n";
    omp_set_num_threads(6);
    int n = 1;

    double time_1 = omp_get_wtime();

	#pragma omp parallel num_threads(8) shared(n) 
    {
        n = omp_get_thread_num();
        cout << n << endl;
        //_sleep(400);
    };
    cout << "n = " << n;
    double time_2 = omp_get_wtime();

    cout << endl;

	#pragma omp parallel
    {
        cout << omp_get_thread_num() << endl;
    };

    int i, t, s = 0;

	#pragma omp parallel private(i,t) reduction(+:s)
    {
		#pragma omp for
        for (i = 1; i < 10; ++i) {
            t = omp_get_thread_num();
            cout << "Thread " << t << " handle element i=" << i << endl;
            s += i;
        };

    };
    cout << "S:" << s << endl;

    cout << time_1 << " " << time_2 << endl;
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
