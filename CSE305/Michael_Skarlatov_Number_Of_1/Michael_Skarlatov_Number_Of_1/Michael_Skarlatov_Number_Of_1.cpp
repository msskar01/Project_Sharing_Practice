//Author: Michael Skarlatov 
//Michael_Skarlatov_Number_Of_1.cpp : Counts the number of ones in a converted binary number
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class NumberOfOnes
{
	public:
		//Constructor
		NumberOfOnes()
		{}

		//Recursive function that counts the ones in a binary number
		int OnesCount(int N) 
		{
			if (N == 0)
			{
				return 0;
			}
			else if (N == 1)
			{
				return 1;
			}
			else
			{
				return OnesCount(N / 2) + OnesCount(N % 2); //Recursive call of the function that counts the 1's
			}
		}
};


int main(int argc, char *argv[])
{
	int number;
	cout << "Enter in a number in base 10 then I'll out put how many 1's in binary it has" << endl;
	//User input
	cin >> number; 
	//Creation of binary object
	NumberOfOnes binary;
	//Output of how many ones made after the conversion
	cout << "There are " << binary.OnesCount(number) << " ones in the number " << number << " when converted to binary" << endl;
    return 0;
}

