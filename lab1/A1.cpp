#include <iostream>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <omp.h>

using namespace std;


int main(int argc, char** argv) {

	// a range vector of size N is defined
	int N = atoi(argv[1]);
	vector<int> V(N);
	iota(V.begin(), V.end(), 1);
	
	// vector is shuffled for the maximum to be found
	random_shuffle(V.begin(), V.end());

	int max_val = V[0];
	clock_t start, finish;

	cout << "Threads  Time" << endl;

	for (int nThreads = 1; nThreads <= 8; nThreads++) {
		start = clock();
		// in every iteration a different number of threads is working
		#pragma omp parallel for reduction (max:max_val) num_threads(nThreads)
			for (int i : V) {
				max_val = max_val > i ? max_val : i;
			}
		finish = clock();
		
		cout << nThreads << "        " << (double (finish - start) / CLOCKS_PER_SEC) << endl;
	}

	cout << endl;
	cout << "Maximum value in vector: " << max_val << endl;

	return 0;

}
