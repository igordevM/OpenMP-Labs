#include <iostream>
#include <time.h>
#include <omp.h>

int main() {
	time_t seed = time(NULL);
	std::cout << "Seed: " << seed << std::endl;
	srand(seed);
	int SIZE;
	std::cout << "Max number of threads: " << omp_get_max_threads() << std::endl;
	std::cout << "Enter massives' size: ";
	std::cin >> SIZE;

	int* A = new int[SIZE];
	int* B = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		A[i] = rand() % 12;
		B[i] = rand() % 12;
	}


	int RESULT = 0;
	double start;
	double end;
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


	RESULT = 0;
	int sum = 0;
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
#pragma omp critical
		{
			RESULT += sum;
		}
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with critical: " << end - start << "Sec" << std::endl;


	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel for shared(A, B) reduction(+:RESULT)
	for (int i = 0; i < SIZE; i++) {
		if ((A[i] + B[i]) > (4 * A[i] - B[i]))
			if ((A[i] + B[i]) > 1)
				RESULT += (A[i] + B[i]);
			else
				if ((4 * A[i] - B[i]) > 1)
					RESULT += (4 * A[i] - B[i]);
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with reduction: " << end - start << "Sec" << std::endl;

	delete A, B;

	return 0;
}

