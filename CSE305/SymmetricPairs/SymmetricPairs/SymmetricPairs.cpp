// SymmetricPairs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <hash_map>
using namespace std;

vector<pair<int, int>> pairs;

bool isSymmetricpair(const pair<int, int> &p1, const pair<int, int> &p2)
{
	return (p1.first == p2.second && p1.second = p2.first);
}

vector<pair<int, int>> findSymmetricpairs(const vector<pair<int, int>> &pairs)
{
	vector<pair<int, int>> rv;
	for(int i =0; i<pairs.size();i++)
		for (int j = i + 1; j < pairs.size(); j++)
		{
			if (isSymmetricpair(pairs[i], pairs[j]))
			{
				rv.push_back(pairs[i]);
			}
		}
}

vector<pair<int, int>> findSymmetricpairs(const vector<pair<int, int>> &pairs)
{
	vector<pair<int, int>> rv;
	unordered_set <<pair<int, int>> ht;
	for (int i = 0; i < pairs.size(); i++)
	{
		pair<int, int> p1 = pairs[i];

		if (ht.find(p1) == ht.end())
		{
			//p1 is not the hash table
			pair<int, int> p2(p1.second, p1.first);
			
		}
	}
	return rv;
}

template <PairHaser>
PairHasher
{
	//hash operator
	int operator (const pair<int, int> & p)
	{
		static hash<int> fn;
		return fn(p.first) + 27 * fn(p.second);
	}
//equlaity operator
bool operator(const pair<int,int> &p1, const parir<int,int> &p2)
{
	return (p1.first == p2.first) && (p1.second = p2.second);
}
}

int main()
{
    return 0;
}

