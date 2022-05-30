#pragma once


template <class T>
class Node
{
	T element;
	Node *left;
	Node *right;
	Node *parent;

	Node(const T& theElement)
	{
		element = theElement;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	~Node()
	{
		delete left;
		delete right;
	}
};

template <class T>
class Const_Iterator
{
	Node<T> * n;
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
