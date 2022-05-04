// CSE611HW6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>

#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>		/* sqrt */

using namespace std;
const size_t n = 1000;

void matrixMulijk(float* C, float* A, float* B)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

void matrixMulikj(float* C, float* A, float* B)
{
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

void matrixMuljik(float* C, float* A, float* B)
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

void matrixMuljki(float* C, float* A, float* B)
{
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++)
		{
			for (int i = 0; i < n; i++)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

void matrixMulkij(float* C, float* A, float* B)
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

void matrixMulkji(float* C, float* A, float* B)
{
	for (int k = 0; k < n; k++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < n; i++)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

#include <omp.h>
void ompMatrixMul(float* C, float* A, float* B)
{
#pragma omp parallel for shared(C, A, B) // starts a parallel region (c++ lambda expression)
	// Assuming row-major storage
	for (int j = 0; j < n; ++j)
	{
		for (int k = 0; k < n; ++k)
		{
			for (int i = 0; i < n; ++i)
			{
				C[i + j * n] += A[i + k * n] * B[k + j * n];
			}
		}
	}
}

int main()
{
	float* A, * B, * C;

	clock_t t;
	t = clock();

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dist(0, 1);

	A = (float*)malloc(sizeof(float) * n * n);
	B = (float*)malloc(sizeof(float) * n * n);
	C = (float*)malloc(sizeof(float) * n * n);

	// initialization
	for (int i = 0; i < n * n; ++i)
		A[i] = 1; //(dist(rd));
	for (int i = 0; i < n * n; ++i)
		B[i] = 1; //(dist(rd));
	for (int i = 0; i < n * n; ++i)
		C[i] = 0;


	// need to reset C every time to get the actual result of the multiplication but in this case since I am using 1 then it will always be 1000 and knowing the result does not really matter
	// since we are just meassuring speed
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to initialize A, B, and C.\n", t, ((float)t) / CLOCKS_PER_SEC);

	t = clock();
	matrixMulijk(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi ijk.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	t = clock();
	matrixMulikj(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi ikj.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	t = clock();
	matrixMuljik(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi jik.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	t = clock();
	matrixMuljki(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi jki.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	t = clock();
	matrixMulkij(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi kij.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	t = clock();
	matrixMulkji(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi kji.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	t = clock();
	ompMatrixMul(C, A, B);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to multi with parallel.\n", t, ((float)t) / CLOCKS_PER_SEC);
	cout << "\n\t C[2] = " << C[2] << "\n\n";

	delete A;
	delete B;
	delete C;
}