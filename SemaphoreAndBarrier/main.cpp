#include <iostream>
#include <time.h>
#include <omp.h>

int main() {
	time_t seed = time(NULL);
	std::cout << "Seed: " << seed << std::endl;
	srand(seed);
	int SIZE, sum = 0, RESULT = 00;
	double start, end;
	omp_lock_t lock;
	std::cout << "Max number of threads: " << omp_get_max_threads() << std::endl;
	std::cout << "Enter massives' size: ";
	std::cin >> SIZE;

	int* A = new int[SIZE];
	int* B = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		A[i] = rand() % 12;
		B[i] = rand() % 12;
	}


	start = omp_get_wtime();
	for (int i = 0; i < SIZE; i++) {
		int sum = 0;
		if ((A[i] + B[i]) > (4 * A[i] - B[i]))
			if ((A[i] + B[i]) > 1)
				RESULT += (A[i] + B[i]);
			else
				if ((4 * A[i] - B[i]) > 1)
					RESULT += (4 * A[i] - B[i]);
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time without OpenMP: " << end - start << "Sec" << std::endl;


	omp_init_lock(&lock);
	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel shared(A, B) private(sum)
	{
		sum = 0;
#pragma omp for 
		for (int i = 0; i < SIZE; i++) {
			if ((A[i] + B[i]) > (4 * A[i] - B[i]))
				if ((A[i] + B[i]) > 1)
					sum += (A[i] + B[i]);
				else
					if ((4 * A[i] - B[i]) > 1)
						sum += (4 * A[i] - B[i]);
		}
		omp_set_lock(&lock);
		RESULT += sum;
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with lock v1: " << end - start << "Sec" << std::endl;


	omp_init_lock(&lock);
	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel for shared(A, B)
	for (int i = 0; i < SIZE; i++) {
		if ((A[i] + B[i]) > (4 * A[i] - B[i]))
			if ((A[i] + B[i]) > 1) {
				omp_set_lock(&lock);
				RESULT += (A[i] + B[i]);
				omp_unset_lock(&lock);
			}
			else
				if ((4 * A[i] - B[i]) > 1) {
					omp_set_lock(&lock);
					RESULT += (4 * A[i] - B[i]);
					omp_unset_lock(&lock);
				}

	}
	omp_destroy_lock(&lock);
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with lock v2: " << end - start << "Sec" << std::endl;


	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel shared(A, B) private(sum) 
	{
		sum = 0;
#pragma omp for /*lastprivate(sum)*/
		for (int i = 0; i < SIZE; i++) {
			if ((A[i] + B[i]) > (4 * A[i] - B[i]))
				if ((A[i] + B[i]) > 1)
					sum += (A[i] + B[i]);
				else
					if ((4 * A[i] - B[i]) > 1)
						sum += (4 * A[i] - B[i]);
		}
#pragma omp barrier
#pragma omp critical
		{
			RESULT += sum;
		}
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with barrier : " << end - start << "Sec" << std::endl;


	delete A, B;

	return 0;
}