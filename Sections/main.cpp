#include <iostream>
#include <time.h>
#include <omp.h>

int main() {
	time_t seed = time(NULL);
	std::cout << "Seed: " << seed << std::endl;
	srand(seed);
	int SIZE, RESULT = 0, sum = 0;
	double start, end;
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


	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp sections private(sum)
		{
#pragma omp section
			{
				sum = 0;
				for (int i = 0; i < SIZE / 2; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							sum += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								sum += (4 * A[i] - B[i]);
				}
				RESULT += sum;
			}
#pragma omp section
			{
				sum = 0;
				for (int i = SIZE / 2; i < SIZE; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							sum += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								sum += (4 * A[i] - B[i]);
				}
				RESULT += sum;
			}
		}
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with 2 sections: " << end - start << "Sec" << std::endl;


	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp sections reduction(+:RESULT)
		{
#pragma omp section
			{
				sum = 0;
				for (int i = 0; i < SIZE / 2; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							RESULT += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								RESULT += (4 * A[i] - B[i]);
				}
			}
#pragma omp section
			{
				sum = 0;
				for (int i = SIZE / 2; i < SIZE; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							RESULT += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								RESULT += (4 * A[i] - B[i]);
				}
			}
		}
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with 2 sections and reduction: " << end - start << "Sec" << std::endl;

	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp sections private(sum)
		{
#pragma omp section
			{
				sum = 0;
				for (int i = 0; i < SIZE / 4; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							sum += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								sum += (4 * A[i] - B[i]);
				}
				RESULT += sum;
			}
#pragma omp section
			{
				sum = 0;
				for (int i = SIZE / 4; i < SIZE / 2; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							sum += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								sum += (4 * A[i] - B[i]);
				}
				RESULT += sum;
			}
#pragma omp section
			{
				sum = 0;
				for (int i = SIZE / 2; i < 3 * SIZE / 4; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							sum += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								sum += (4 * A[i] - B[i]);
				}
				RESULT += sum;
			}
#pragma omp section
			{
				sum = 0;
				for (int i = 3 * SIZE / 4; i < SIZE; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							sum += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								sum += (4 * A[i] - B[i]);
				}
				RESULT += sum;
			}
		}
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with 4 sections: " << end - start << "Sec" << std::endl;


	RESULT = 0;
	start = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp sections reduction(+:RESULT)
		{
#pragma omp section
			{
				sum = 0;
				for (int i = 0; i < SIZE / 4; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							RESULT += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								RESULT += (4 * A[i] - B[i]);
				}
			}
#pragma omp section
			{
				sum = 0;
				for (int i = SIZE / 4; i < SIZE / 2; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							RESULT += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								RESULT += (4 * A[i] - B[i]);
				}
			}
#pragma omp section
			{
				sum = 0;
				for (int i = SIZE / 2; i < 3 * SIZE / 4; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							RESULT += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								RESULT += (4 * A[i] - B[i]);
				}
			}
#pragma omp section
			{
				sum = 0;
				for (int i = 3 * SIZE / 4; i < SIZE; i++) {
					if ((A[i] + B[i]) > (4 * A[i] - B[i]))
						if ((A[i] + B[i]) > 1)
							RESULT += (A[i] + B[i]);
						else
							if ((4 * A[i] - B[i]) > 1)
								RESULT += (4 * A[i] - B[i]);
				}
			}
		}
	}
	end = omp_get_wtime();
	std::cout << "Result: " << RESULT << "; Time with OpenMP with 4 sections and reduction: " << end - start << "Sec" << std::endl;


	delete A, B;

	return 0;
}

