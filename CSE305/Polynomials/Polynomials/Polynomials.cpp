// Polynomials.cpp : Defines the entry point for the console application.
//

#include"stdafx.h"
#include<iostream>
#include<vector>

using namespace std;

//Product making class
class sparseProduct 
{
public:
	vector<vector<int>> product;
	sparseProduct(vector<vector<int>> productNormal)
	{
		for (int i = 0; i < productNormal.size(); i++)
		{
			this->product.push_back(productNormal[i]);
		}
	}

	//Prints polynomial
	void print()
	{
		for (int i = 0; i < this->product.size() - 1; i++)
		{
			cout << this->product[i][1] << "X^" << this->product[i][0] << " + ";
		}
		cout << this->product[product.size() - 1][1] << "X^" << this->product[product.size() - 1][0] << "\n";
	}

	//Replaces Polynomials
	void replace()
	{
		vector<int> variable;
		variable.push_back(2);
		variable.push_back(3);
		for (int k = 0; k<this->product.size(); k++)
		{
			if (this->product[k][0] == variable[0])
			{
				variable[1] = variable[1] + this->product[k][1];
				this->product.at(k) = variable;
				variable.clear();
			}
		}
	}

	//Function that multiplies and sort the polynomials
	void PolyMaker(vector<vector<int>> Product2)
	{
		vector<vector<int>> newVector;
		vector<vector<int>> sortedVector;
		vector<int> variable;
		vector<int> highest_exponent;
		int highest_exponentInd = 0;
		//Multiplies and adds like terms like Foiling
		for (int i = 0; i < this->product.size(); i++)
		{
			for (int j = 0; j < Product2.size(); j++)
			{
				variable.push_back(this->product[i][0] + Product2[j][0]);
				variable.push_back(this->product[i][1] * Product2[j][1]);
				for (int k = 0; k < newVector.size(); k++)
				{
					if (newVector[k][0] == variable[0])
					{
						variable[1] = variable[1] + newVector[k][1];
						newVector.at(k) = variable;
						variable.clear();
						break;
					}
				}
				if (!variable.empty())
				{
					if (variable[1] != 0)
					{
						newVector.push_back(variable);
						variable.clear();
					}
				}
			}
		}

		//Sorts
		variable.clear();
		int OriginalSize = newVector.size();
		for (int i = 0; i < OriginalSize; i++)
		{
			highest_exponent.clear();
			highest_exponent.push_back(newVector[0][0]);
			highest_exponent.push_back(newVector[0][1]);
			highest_exponentInd = 0;
			for (int j = 0; j < newVector.size(); j++)
			{
				if (highest_exponent[0] < newVector[j][0])
				{
					highest_exponent[0] = newVector[j][0];
					highest_exponent[1] = newVector[j][1];
					highest_exponentInd = j;
				}
			}
			sortedVector.push_back(highest_exponent);
			variable = newVector[newVector.size() - 1];
			newVector.at(highest_exponentInd) = variable;
			newVector.pop_back();
		}
		this->product.clear();
		for (int i = 0; i < sortedVector.size(); i++)
			this->product.push_back(sortedVector[i]);
	}
};

int main()
{
	vector<vector<int>> Productn;
	vector<int> Variable;
	Variable.push_back(5);
	Variable.push_back(2);
	Productn.push_back(Variable);
	Variable.clear();
	Variable.push_back(8);
	Variable.push_back(1);
	Productn.push_back(Variable);
	Variable.clear();
	Variable.push_back(4);
	Variable.push_back(3);
	Productn.push_back(Variable);
	Variable.clear();
	sparseProduct P1(Productn);
	Productn.clear();
	Variable.push_back(3);
	Variable.push_back(2);
	Productn.push_back(Variable);
	Variable.clear();
	Variable.push_back(2);
	Variable.push_back(2);
	Productn.push_back(Variable);
	Variable.clear();
	Variable.push_back(3);
	Variable.push_back(4);
	Productn.push_back(Variable);
	sparseProduct P2(Productn);
	cout << "  ";
	P1.print();
	cout << "* ";
	P2.print();
	P1.PolyMaker(P2.product);
	cout << "  ";
	P1.print();
	return 0;
}
