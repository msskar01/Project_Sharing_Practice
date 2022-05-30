// Author: Michael Skarlatov
//Checks the runtime of functions

#include "stdafx.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;
#define G

//All of the different functions being tested
#ifdef A
int run(int num)
{
	int sum = 0;
	for (int i = 0; i < num; ++i)
	{
		++sum;
	}
	return sum;
}
#endif

#ifdef B
int run(int num)
{
	int sum = 0;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			++sum;
		}
	}
	return sum;
}
#endif

#ifdef C
int run(int num)
{
	int sum = 0;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num * num; ++j)
		{
			++sum;
		}
	}
	return sum;
}
#endif

#ifdef D
int run(int num)
{
	int sum = 0;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			++sum;
		}
	}
	return sum;
}
#endif

#ifdef E
int run(int num)
{
	int sum = 0;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < i * i; ++j)
		{
			for (int k = 0; k < j; ++k)
			{
				++sum;
			}
		}
	}
	return sum;
}
#endif

#ifdef F
int run(int num)
{
	int sum = 0;
	for (int i = 1; i < num; ++i)
	{
		for (int j = 1; j < i * i; ++j)
		{
			if (j % i == 0)
			{
				for (int k = 0; k < j; ++k)
				{
					++sum;
				}
			}
		}
	}
	return sum;
}
#endif

#ifdef G
int run(int num)
{
	int sum = 0;
	for (int j = 1; j < num; j *= 2)
	{
		++sum;
	}
	return sum;
}
#endif

//Main which uses chrono to measure runtime
int main()
{
	int num = 0;
	cout << "Please enter an integer" << endl;
	cin >> num;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cout << run(num) << endl;
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "Total runtime of Funciton : " << duration << endl;
    return 0;
}

