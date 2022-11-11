#include <iostream>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <omp.h>

using namespace std;


int main(int argc, char** argv) {

	// N random arrays of size N (with numbers 1-100) are defined
	int N = atoi(argv[1]);
	int randMatrix1[N][N];
	int randMatrix2[N][N];
	int resMatrix[N][N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			randMatrix1[i][j] = rand()%100 + 1;
			randMatrix2[i][j] = rand()%100 + 1;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// aboba with the multiplication
		}
	}



	//clock_t start, finish;

	//cout << "Threads  Time" << endl;

	//for (int nThreads = 1; nThreads <= 10; nThreads++) {
		//start = clock();
		// in every iteration a different number of threads is working
		//#pragma omp parallel for reduction (max:max_val) num_threads(nThreads)
			//for (int i : V) {
				//max_val = max_val > i ? max_val : i;
			//}
		//finish = clock();
		
		//cout << nThreads << "        " << (double (finish - start) / CLOCKS_PER_SEC) << endl;
	//}

	//cout << endl;
	//cout << "Maximum value in vector: " << max_val << endl;

	return 0;

}
