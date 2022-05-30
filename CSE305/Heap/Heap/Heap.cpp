// Heap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(*a)

using namespace std;

//Generic swap funciton
void swap(float &a, float &b)
{
	float temp = a;
	a = b;
	b = temp;
}

//Comperitors
bool Greater(int a, int b)
{
	return a > b;
}

bool Smaller(int a, int b)
{
	return a < b;
}

//Average function
float Average(float a, float b)
{
	return (a + b) / 2;
}

//Function to campare the size of the heaps and determine which heap (either maxheap or minheap) is larger, smaller, or same size 
int SizeCompare(int a, int b)
{
	if (a == b)
	{
		return 0;
	}
	return a < b ? -1 : 1;
}

//Class for generic heap creation
class Heap
{
public:
	Heap(float *location, bool (*c)(int a, int b)) : A(location), comp(c)
	{
		heapSize = -1;
	}
	~Heap()
	{
		if (A)
		{
			delete[] A;
		}
	}
	virtual bool Insert(int value) = 0;
	virtual float  GetTop() = 0;
	virtual float  ExtractTop()=0;
	virtual int  GetCount() = 0;

protected:
	//Retruns the left or right child for part of the heap in the array location
	int left(int i)
	{
		return 2 * i + 1;
	}
	int right(int i)
	{
		return 2 * (i + 1);
	}
	//Returns the center of an array as the parent for a heap
	int parent(int i)
	{
		if (i <= 0)
		{
			return -1;
		}
		return (i - 1) / 2;
	}

	//Heap array 
	float *A;
	//Comparator 
	bool(*comp)(int a, int b);
	//Heap size 
	int heapSize;

	float top(void)
	{
		float max = -1;
		if (heapSize >= 0)
		{
			max = A[0];
		}
		return max;
	}
	int count()
	{
		return heapSize + 1;
	}

	void heapify(int i)
	{
		int p = parent(i);
		//Compares maxheap and minheap
		//Percolates up
		if (p >= 0 && comp(A[i], A[p]))
		{
			swap(A[i], A[p]);
			heapify(p);
		}
	}

	int deleteTop()
	{
		int del = -1;
		if (heapSize > del)
		{
			del = A[0];
			swap(A[0], A[heapSize]);
			heapSize--;
			heapify(parent(heapSize + 1));
		}
		return del;
	}

	bool insertHelper(int key)
	{
		if (heapSize < 128)
		{
			heapSize++;
			A[heapSize] = key;
			heapify(heapSize);
			return true;
		}
		return false;
	}
};

class MaxHeap : public Heap
{
private:

public:
	MaxHeap() : Heap(new float[100], &Greater) {  }

	~MaxHeap() { }

	//Wrapper to return root of Max Heap 
	float GetTop()
	{
		return top();
	}

	//Wrapper to delete and return root of Max Heap 
	float ExtractTop()
	{
		return deleteTop();
	}

	//Wrapper to return # elements of Max Heap 
	int  GetCount()
	{
		return count();
	}

	//Wrapper to insert into Max Heap 
	bool Insert(int key)
	{
		return insertHelper(key);
	}
};

class MinHeap : public Heap
{
private:

public:

	MinHeap() : Heap(new float[100], &Smaller) { }

	~MinHeap() { }

	//Wrapper to return root of Min Heap 
	float GetTop()
	{
		return top();
	}

	//Wrapper to delete and return root of Min Heap 
	float ExtractTop()
	{
		return deleteTop();
	}

	//Wrapper to return # elements of Min Heap 
	int  GetCount()
	{
		return count();
	}

	// Wrapper to insert into Min Heap 
	bool Insert(int key)
	{
		return insertHelper(key);
	}
};

//Function implementing algorithm to find median
float getMedian(float value, float &m, Heap &l, Heap &r)
{
	//Checks if the heaps are balanced. If yes it will return 0
	int sizeHeap = SizeCompare(l.GetCount(), r.GetCount());
	switch (sizeHeap)
	{
	case 1: //There are more elements in left (max) heap 

		if (value < m) //Max elements in left side
		{
			//Remove top element from left heap and insert into right heap 
			r.Insert(l.ExtractTop());
			//current element fits in left max heap 
			l.Insert(value);
		}
		else
		{
			//current element fits in right min heap 
			r.Insert(value);
		}

		//Both heaps are balanced 
		m = Average(l.GetTop(), r.GetTop());

		break;

	case 0: //The left and right heaps contain same number of elements 

		if (value < m) //Current element fits in left max heap 
		{
			l.Insert(value);
			m = l.GetTop();
		}
		else
		{
			//Current element fits in right min heap 
			r.Insert(value);
			m = r.GetTop();
		}

		break;

	case -1: //There are more elements in right min heap 

		if (value < m) //Current element fits in left max heap 
		{
			l.Insert(value);
		}
		else
		{
			//Remove top element from right heap and insert into left heap 
			l.Insert(r.ExtractTop());

			//Current element fits in right min heap 
			r.Insert(value);
		}

		//Both heaps are balanced 
		m = Average(l.GetTop(), r.GetTop());

		break;
	}
	return m;
}

void printMedian(float A[], int size)
{
	float m = 0; //Effective median 
	Heap *left = new MaxHeap();
	Heap *right = new MinHeap();
	for (int i = 0; i < size; i++)
	{
		m = getMedian(A[i], m, *left, *right);
		cout << "The median after adding " << A[i] << " is ";
		cout << m << endl;
	}
	//Delete the left and right heaps
	delete left;
	delete right;
}
 
int main()
{
	float A[] = { 1, 4, 6, 3, 2, 8 };
	int size = ARRAY_SIZE(A);
	//Print out the stream and medians
	printMedian(A, size);
	return 0;
}