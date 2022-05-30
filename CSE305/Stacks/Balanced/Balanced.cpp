// Balanced.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

bool Balanced(const string & str)
{
	stack<char> s;
	for (const char & c : str)
	{
		if (c == '{' || c == '[' || c == '(')
		{
			s.push(c);
		}
		else if (c == '}')
		{
			if (s.empty() || s.top() != '{')
			{
				return false;
			}
			s.pop();
		}
		else if(c == ']')
		{
			if (s.empty() || s.top() != '[')
			{
				return false;
			}
			s.pop();
		}
		else if (c == ')')
		{
			if (s.empty() || s.top() != '(')
			{
				return false;
			}
			s.pop();
		}

	}
	return s.empty();
}

int main()
{
	string strs[] = { "({[()]})", "(())", "[)", "}", "(" };
	for (string str : strs)
	{
		cout << boolalpha << str << "  ->  " << Balanced(str) << endl;
	}
    return 0;
}

