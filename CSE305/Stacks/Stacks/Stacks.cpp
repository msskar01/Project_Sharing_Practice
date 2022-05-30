// Stacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>

using namespace std;

class Stack
{
private:
	int *a;
	int length;
	int max;

public:
	Stack(int size) : max(size), length(0), a(new int[max])
	{}

	~Stack()
	{
		delete[] a;
	}

	int top()
	{
		return a[length];
	}

	void push_back(int i)
	{
		a[length] = i;
		++length;
	}

	void pop_back()
	{
		--length;
	}
};

int main()
{
	Stack s(10);
	s.push_back(1);
	s.push_back(2);
	s.push_back(3);
	cout << s.top() << endl;
	s.pop_back();
	cout << s.top() << endl;
    return 0;
}