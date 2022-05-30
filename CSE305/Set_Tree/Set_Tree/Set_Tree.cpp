// Set_Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Class templates
template <class T> class Set;
template <class T> class Const_Iterator;

//The tree node struct that sets up all of the pointers in the nodes, including the addition of the parent pointer
template <class T>
struct SetNode
{
	T element;
	SetNode *left;
	SetNode *right;
	SetNode *parent;

	SetNode(const T& theElement)
	{
		element = theElement;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	~SetNode()
	{
		delete left;
		delete right;
	}
};

//The classs for the set
template <class T>
class SetTree
{
public:
	size_t _size;
	SetNode<T> *root;
	mutable SetNode<T> *startIterator;

	SetTree() : _size{ 0 }, root{ nullptr }, startIterator{ nullptr }
	{}

	~SetTree()
	{
		clear();
	}

	//Making of iterator with iterator class
	using iterator = Const_Iterator<T>;

	//Basic methods for the set to make and insert into a binary tree
	SetTree(const SetTree &s)
	{
		_size = 0;
		root = nullptr;
		for (iterator it = s.begin(); it != s.end(); it++)
		{
			insert(*it);
		}
	}

	SetTree& operator =(const SetTree &s)
	{
		if (&s == this)
		{
			return *this;
		}

		clear();
		for (iterator it = s.begin(); it != s.end(); it++)
		{
			insert(*it);
		}
		return *this;
	}

	void clear()
	{
		if (root)
		{
			delete root;
			root = nullptr;
			_size = 0;
		}
	}

	size_t size() const
	{
		return _size;
	}

	bool empty() const
	{
		return _size == 0;
	}
	
	T& insert(const T& t)
	{
		return insert_imp(t, root, _size);
	}

	iterator begin() const
	{
		build_iterators(root);
		return iterator(startIterator);
	}

	iterator middle() const
	{
		return iterator(root);
	}

	iterator end() const 
	{
		return iterator(0);
	}

private:
	//Funtion to build the iterator
	void build_iterators(const SetNode<T> *r) const
	{
		size_t i;
		vector<SetNode<T>*> iterators;
		build_iterators_imp(iterators, r);

		if (empty())
		{
			startIterator = nullptr;
			return;
		}

		startIterator = iterators[0];
		for (i = 0; i < iterators.size() - 1; i++)
		{
			iterators[i]->parent = iterators[i + 1];
		}
		iterators[i]->parent = nullptr;
	}

	//Function called by the building of the iterator, uses recurtion to set up nodes in the iterator
	static void build_iterators_imp(vector<SetNode<T>*> &iterators, const SetNode<T> *r)
	{
		if (r == nullptr)
		{
			return;
		}

		build_iterators_imp(iterators, r->left);

		iterators.push_back((SetNode<T>*)r);

		build_iterators_imp(iterators, r->right);
	}

	//Function used in the insert tht uses recursion to actually insert the value
	static T& insert_imp(const T& t, SetNode<T> *&r, size_t &_size)
	{
		if (!r)
		{
			_size++;
			r = new SetNode<T>(t);
			return r->element;
		}

		if (t == r->element)
		{
			return r->element;
		}
		else if (t < r->element)
		{
			return insert_imp(t, r->left, _size);
		}
		else
		{
			return insert_imp(t, r->right, _size);
		}
	}
};

//Class for setting up the iterator and its opperations
template <class T>
class Const_Iterator
{
	SetNode<T> * n;
public:
	Const_Iterator() : n(null)
	{}
	Const_Iterator(SetNode<T> * newNode) : n(newNode) 
	{}

	bool operator == (Const_Iterator it) const 
	{
		return n == it.n;
	}
	bool operator != (Const_Iterator it) const 
	{
		return n != it.n; 
	}

	Const_Iterator & operator++();
	Const_Iterator operator++(int);

	T & operator*() 
	{
		return n->element;
	}
	T * operator->() 
	{
		return &n->element;
	}
	Const_Iterator & operator=(Const_Iterator<T> it) 
	{
		n = it.n;
		return *this;
	}

	friend class Set<T>;
};

template <class T>
Const_Iterator<T>& Const_Iterator<T>::operator ++()
{
	n = n->parent;
	return *this;
}

template <class T>
Const_Iterator<T> Const_Iterator<T>::operator ++(int)
{
	Const_Iterator<T> it(*this);
	++(*this);

	return it;
}

//Stuff in the main to insert into the set and then print out to show the set is working
int main()
{
	SetTree<string> set1;
	SetTree<int> set;
	set.insert(9); set.insert(2);
	set.insert(2); set.insert(7);
	set.insert(0); set.insert(0);
	set.insert(6); set.insert(1);
	set.insert(12); set.insert(11);
	set.insert(8); set.insert(10);
	set.insert(5); set.insert(0);
	set.insert(3); set.insert(2);
	set.insert(7); set.insert(4);
	set.insert(4); set.insert(4);
	set.insert(9); set.insert(7);
	set.insert(11); set.insert(4);

	set1.insert("Hello"); set1.insert("HELlo");
	set1.insert("heLLO");

	for (SetTree<int>::iterator it = set.begin(); it != set.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << endl;
	SetTree<int>::iterator it = set.middle();
	cout << *it << endl;
	for (SetTree<string>::iterator it1 = set1.begin(); it1 != set1.end(); it1++)
	{
		cout << *it1 << endl;
	}
    return 0;
}

