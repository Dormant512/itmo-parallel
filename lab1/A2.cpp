#include <iostream>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <omp.h>

using namespace std;


void printMatrix(int N, double **M) {
	cout << "Matrix:" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void matMul(int N, double **M1, double **M2, double **Mres, string order="ijk") {
	int ind1, ind2, ind3;
	double t, t1;
	
	cout << "Index order: " << order << endl;
	cout << "Threads\t\tTime\t\tEfficiency" << endl;
	
	for (int nThreads = 1; nThreads <= 10; nThreads++) {
		if (nThreads == 1) {
			t1 = omp_get_wtime();
			t = t1;
		} else {
			t = omp_get_wtime();
		}

		#pragma omp parallel num_threads(nThreads) shared(N) private(ind1,ind2,ind3)
		{
		#pragma for collapse(3) schedule(static)
			for (int ind1 = 0; ind1 < N; ind1++) {
				for (int ind2 = 0; ind2 < N; ind2++) {
					for (int ind3 = 0; ind3 < N; ind3++) {
						if (order == "ijk") {
							Mres[ind1][ind2] += M1[ind1][ind3] * M2[ind3][ind2];
						} else if (order == "ikj") {
							Mres[ind1][ind3] += M1[ind1][ind2] * M2[ind2][ind3];
						} else if (order == "jik") {
							Mres[ind2][ind1] += M1[ind2][ind3] * M2[ind3][ind1];
						} else if (order == "jki") {
							Mres[ind3][ind1] += M1[ind3][ind2] * M2[ind2][ind1];
						} else if (order == "kij") {
							Mres[ind2][ind3] += M1[ind2][ind1] * M2[ind1][ind3];
						} else if (order == "kji") {
							Mres[ind3][ind2] += M1[ind3][ind1] * M2[ind1][ind2];
						}
					}
				}
			}
		}

		if (nThreads == 1) {
			t1 = omp_get_wtime() - t1;
			t = t1;
		} else {
			t = omp_get_wtime() - t;
		}

		cout << nThreads << "\t\t" << round(t * 10e5) / 10e5 << "\t\t" << round(t1 * 10e6 / t) / 10e6 << endl;
	}

}


int main(int argc, char **argv) {

	// N random arrays of size N (with numbers 1-100) are defined
	int N = atoi(argv[1]);
	double **randMatrix1, **randMatrix2, **resMatrix;

	randMatrix1 = new double *[N];
	randMatrix2 = new double *[N];
	resMatrix = new double *[N];

	for (int i = 0; i < N; i++) {
		randMatrix1[i] = new double[N];
		randMatrix2[i] = new double[N];
		resMatrix[i] = new double[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			randMatrix1[i][j] = rand() % 100;
			randMatrix2[i][j] = rand() % 100;
		}
	}

	string orderArray[6] = {"ijk", "ikj", "jik", "jki", "kij", "kji"};
		for (string &ord : orderArray) {
			matMul(N, randMatrix1, randMatrix2, resMatrix, ord);
			cout << endl;
		}

	//cout << endl;
	//printMatrix(N, resMatrix);

	return 0;

}
