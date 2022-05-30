// Max_Subsequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <climits>

using namespace std;

int max_subseq(int arr[], int n)
{
	int maxsum = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int sum = 0;
			for (int k = i; k <= j; k++)
			{
				sum = sum + arr[k];
			}
			if (sum > maxsum)
			{
				maxsum = sum;
			}
		}
	}

	return maxsum;
}
int main()
{
	int list[] = { -2, 11, -4, 13, -5, -2 };
	cout << max_subseq(list, 6) << endl;
    return 0;
}

