//Author: Michael Skarlatov
//Michael_Skarlatov_Permutation.cpp : Finds all the permutations of a string
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void permute(const string & str);
void permute(const string & str, int low, int high);

//Method that is called first and starts the low and high at the begining and end of the string
void permute(const string & str)
{
	permute(str, 0, str.size() - 1);
}

//Method that dose the actual permutation
void permute(const string & str, int low, int high)
{
	//Prints out each permutation
	if (low == high)
	{
		cout << "- " << str << endl;
	}
	//Swaps the letters in the string while also recursivley calling the function to print out all the permutaions
	else
	{ 
		string Temp = str;
		for (int i = low; i <= high; i++)
		{
			swap(Temp[low], Temp[i]);
			permute(Temp, low + 1, high);
		}
	}
}

int main()
{
	//Main function where the user inputs the string and the list permutations are outputed
	string str;
	cout << "Please input a string" << endl;
	cin >> str;
	permute(str);
	cout << "These are the permutations for " << str << endl;
    return 0;
}

