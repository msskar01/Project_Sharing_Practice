// Binary_Search_Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ostream>
using namespace std;

//Structer that builds all the information for a node in the tree
template <class T>
struct BinaryNode 
{
	T element;// The data in the node 
	BinaryNode	*left; // Left child
	BinaryNode *right; // Right child 
	BinaryNode(T value)//Giving a node a value
	{
		this->element = value;
		this->left = this->right = nullptr;
	}
}; 

//The Binary Search Tree
template <class T>
class BinarySearchTree
{
public:
	BinaryNode<T> * root;

	BinarySearchTree()//Constructor
	{
		this->root = nullptr;
	}

	BinaryNode* insert(BinaryNode* r, int value)//Insert function that inserts a value into the tree
	{
		if (r == nullptr)
		{
			BinaryNode *node = new BinaryNode(value);
			return node;
		}

		if (r->element <= value)
		{
			r->right = insert(r->right, value);
			return r;
		}
		else if (r->element > value)
		{
			r->left = insert(r->left, value);
			return r;
		}
	}

	void print(BinaryNode* r)//Print function that prints out the tree inorder
	{
		if (r != nullptr)
		{
			print(r->left);
			cout << r->element << endl;
			print(r->right);
		}
	}

	bool compair(BinaryNode *t1, BinaryNode *t2)//Function that compairs two trees
	{
		if (t1 == nullptr && t2 == nullptr)
		{
			return true;
		}
		if (t1 != nullptr && t2 != nullptr)
		{
			return compair(t1->right, t2->right);
			return compair(t2->left, t2->left);
		}
		return false;
	}

	int computeNodes(BinaryNode *T)//Function that counts the amount of nodes in a tree O(n)
	{
		int numberOfNodes = 0;
		if (T != nullptr)
		{
			++numberOfNodes;
			numberOfNodes += computeNodes(T->left);
			numberOfNodes += computeNodes(T->right);
		}
		return numberOfNodes;
	}

	int computeLeaves(BinaryNode *T)//Function that counts the amount leaves on a tree O(n)
	{
		int numberOfLeaves = 0;
		if (T != nullptr)
		{
			numberOfLeaves += computeLeaves(T->left);
			numberOfLeaves += computeLeaves(T->right);
			if (T->left == nullptr && T->right == nullptr)
			{
				return ++numberOfLeaves;
			}
		}
		return numberOfLeaves;
	}

	int computeFullNodes(BinaryNode *T)//Function that counts all the full nodes on a tree O(n)
	{
		int numberOfFull = 0;
		if (T != nullptr)
		{
			numberOfFull += computeFullNodes(T->left);
			numberOfFull += computeFullNodes(T->right);
			if (T->left != nullptr && T->right != nullptr)
			{
				++numberOfFull;
			}
		}
		return numberOfFull;
	}

	bool isBST(BinaryNode * root, int max, int min)
	{
		if (root == nullptr)
		{
			return true;
		}
		else if (root->left->element > min || root->right->element <= max)
		{
			return false;
		}
		else
		{
			return(isBST(root->left, min, root->left->element) && isBST(root->right, root->right->element, max));
		}
	}
};

int main()
{
	//Creation of a tree and insertion of numbers for testing
	BinarySearchTree<int> BT;
	BT.root = BT.insert(BT.root, 3);
	BT.insert(BT.root, 1);
	BT.insert(BT.root, 4);
	BT.insert(BT.root, 6);
	BT.insert(BT.root, 9);
	BT.insert(BT.root, 2);
	BT.insert(BT.root, 5);
	BT.insert(BT.root, 7);

	cout << "Input numbers  3, 1, 4, 6, 9, 2, 5, 7 " << endl;
	//Outputts the functions values
	BT.print(BT.root);
	cout << "number of nodes " << BT.computeNodes(BT.root) << endl;
	cout << "number of leaves " << BT.computeLeaves(BT.root) << endl;
	cout << "number of full nodes " << BT.computeFullNodes(BT.root) << endl;
    return 0;
}

