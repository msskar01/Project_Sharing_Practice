// SpellChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;
typedef unordered_map<string, string> dictionary;

bool search(string s, const dictionary &d)
{
	string str = s;
	string Ls;
	Ls.resize(str.size());
	transform(str.begin(), str.end(), Ls.begin(), ::tolower);
	auto const found = d.find(Ls);
	if (found != d.end())
	{
		return true;
	}
	return false;
}

void swapSearch(string s, const dictionary &d, int n, string twoStr)
{
	string tempstr = s;
	if (n == 1)
	{
		if (search(twoStr + tempstr, d))
		{
			cout << "Alternative: " << twoStr + tempstr << endl;
		}
		return;
	}
	for (int i = 0; i<n; i++)
	{
		swapSearch(tempstr.substr(1), d, n - 1, twoStr + tempstr[0]);
		rotate(tempstr.begin(), tempstr.begin() + 1, tempstr.end());
	}
}

void removeLetter(string word, dictionary d)
{
	string tempstr = word;
	for (int q = 0; q < tempstr.size(); q++)
	{
		tempstr.erase(tempstr.begin() + q);
		if (search(tempstr, d))
		{
			cout << "Alternative: " << tempstr << endl;
		}
		tempstr = word;
	}
}

void addLetters(string word, dictionary d, char Alpha[26])
{
	string tempstr = word;
	for (int k = 0; k < sizeof(Alpha); k++)
	{
		for (int l = 0; l < word.size() + 1; l++)
		{
			tempstr.insert(l, 1, Alpha[k]);
			if (search(tempstr, d))
			{
				cout << "Alternative: " << tempstr << endl;
			}
			tempstr = word;
		}
	}
}

vector<string> read(string filename)
{
	vector<string> str;
	ifstream f;
	string s;
	f.open(filename);
	while (f)
	{
		getline(f, s);
		if (f)
		{
			str.push_back(s);
		}
	}
	return str;
}

vector<vector<string>> breakParagraph(vector<string> line)
{
	vector<vector<string>> paragraph;
	for (int k = 0; k < line.size(); k++)
	{
		string s = line[k];
		string delimiter = " ";
		vector<string> strV;
		size_t pos = 0;
		string token;
		while ((pos = s.find(delimiter)) != string::npos)
		{
			token = s.substr(0, pos);
			strV.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		strV.push_back(s);
		paragraph.push_back(strV);
	}
	return paragraph;
}

string removeChar(string &s, int index) 
{
	string output; 
	for (int i = 0; i < index; i++) 
	{ 
		output += s[i]; 
	} 
	for (int i = index + 1; i < s.size(); i++)
	{ 
		output += s[i];
	} 
	return output;
}

dictionary getDict(string filename) 
{
	dictionary r; 
	ifstream f;
	f.open(filename);
	string str, Lstr;
	while (f) 
	{
		getline(f, str);
		Lstr.resize(str.size());
		transform(str.begin(), str.end(), Lstr.begin(), ::tolower);
		// read the line 
		r.emplace(Lstr, Lstr);
	}
	f.close(); //close the file 
	return r;
}

void searchFile(string filename, const dictionary &d)
{
		ifstream f;
		f.open(filename); 
		string str; 
		while (f) 
		{
			getline(f, str); // read the line
		} f.close(); //close the file
} 

int main(int argc, char **argv) 
{ 
	char Alpha[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	dictionary d = getDict("Words.txt"); 
	vector<string> line = read("MyWords.txt");
	vector<vector<string>> paragraph; 
	paragraph = breakParagraph(line);

	for (int i = 0; i < paragraph.size(); i++)
	{
		for (int j = 0; j < paragraph[i].size(); j++)
		{
			if (!search(paragraph[i][j], d))
			{	
				cout << paragraph[i][j] << " is not found on line " << i + 1 << endl;
				string tempstr = paragraph[i][j];

				//Add letters function
				addLetters(tempstr, d, Alpha);

				//Remove a letter function
				removeLetter(tempstr, d);

				//Permute the word function
				string st = "";
				swapSearch(tempstr, d, tempstr.size(), st);
			}
		}
	}
	return 0;
}