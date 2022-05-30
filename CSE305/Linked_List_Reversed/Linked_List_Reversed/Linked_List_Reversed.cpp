//Author: Michael Skarlatov
//An algorithm that can print a singly linked list in reverse
#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//Linked list node struct, this allows the creation of nodes which can be used in the linked list
struct ll_node
{
private:

public:
	int val;
	ll_node *next;

	//This is the method that alows me to set the value of a node
	ll_node(int value)
	{
		this->val = value;
		this->next = nullptr;
	}
};

//Linked list class with all of the parts and functions of a linked list
class linked_list
{
private:


public:
	//The head and tail of the list
	ll_node *head;
	ll_node *tail;

	//Constructor that initializes the head and tail nodes
	linked_list()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	//The add function which allows values to be added to the list
	void add(int value)
	{
		ll_node *node = new ll_node(value);
		if (this->head == nullptr)
		{
			this->head = node;
		}
		else
		{
			this->tail->next = node;
		}
		this->tail = node;
	}

	//This function is one of the ways I was able to complete the assignment.
	//This funciton allows me to take a linked list and flip all of its linkes to point at the previous node with out maked any new linkes
	//It then sets the head equal to the node at the end of the list and tail at the beging of the list
	void reversedList()
	{
		ll_node *currentPos, *nextPos, *previousPos;
		previousPos = nullptr;
		currentPos = head;
		nextPos = nullptr;
		while (currentPos != nullptr)
		{
			nextPos = currentPos->next;
			currentPos->next = previousPos;
			previousPos = currentPos;
			currentPos = nextPos;
		}
		tail = head;
		head = previousPos;
	}

	//This function prints out the whole list from head to tail
	void print()
	{
		ll_node *temp = head;
		while (temp != nullptr)
		{
			cout << temp->val << " ";
			temp = temp->next;
		}
	}

	//This function was the second way I was able to complete the assignment.
	//This function printed out the list in reverse without flipping any of the linkes and unchanging the list 
	//It did this by counting how long the list was and then using a double for loop to keep track of where the end of the list -1 would be
	void printReverse()
	{
		int count = 0;
		for (ll_node *print = head; print != nullptr; print = print->next)
		{
			count++;
		}
		for (; count > 0; count--)
		{
			ll_node *temp = head;
			for (int i = 1; i < count; i++)
			{
				temp = temp->next;
			}
			cout << temp->val << " ";;
		}
	}
};


int max(int x, int y, int z)
{
	int m = x > y ? x : y;
	return m > z ? m : z;
}
int min(int x, int y, int z)
{
	int m = x < y ? x : y;
	return m < z ? m : z;
}
int maxSubProd(vector<int> v)
{
	int minP = 1;
	int maxP = 1;
	for (auto x : v)
	{
		int min_ = minP;
		int max_ = maxP;
		minP = min(min_, min_*x, max_*x);
		maxP = max(min_, min_*x, max_*x);
	}
	return maxP;
}

class queue
{
private:
	int head = 0;
	int tail = 0;

public:
	vector<int> j;
	void enqueue(int value)
	{
		if (tail == head)
		{
			j[head] = value;
			this.tail;
		}
	}
};

//Main function
int main(int argc, char *argv[])
{
	//Creation of list and the addition of elements to the list
	linked_list ll;
	ll.add(1);
	ll.add(2);
	ll.add(3);

	//Outputs of the list and reversed list with explination of process
	cout << "Given list" << endl;
	ll.print();
	cout << endl;
	cout << "Printed list in reverse without chaning the list" << endl;
	ll.printReverse();
	cout << endl;
	cout << "This means that the list's head is still " << ll.head->val << " and the list's tail is still " << ll.tail->val << endl;
	cout << "Printed list in reverse by flipping all of the list's pointers and then reprinting the list" << endl;
	ll.reversedList();
	ll.print();
	cout << endl;
	cout << "This means that the new head would be " << ll.head->val << " and the new tail would be " << ll.tail->val << endl;

	vector<int> p = { 1,2,3,4,5,6 };
	cout << maxSubProd(p) << endl;

	delete &ll;
	return 0;
}
