#include "stdafx.h"
#include <iostream>
using namespace std;

struct ll_node
{
private:

public:
	int val;
	ll_node *prev;
	ll_node *next;

	ll_node(int value)
	{
		this->val = value;
		this->next = nullptr;
	}
};

class linked_list
{
private:

public:
	ll_node *head;
	ll_node *tail;

	linked_list()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	void add(int end)
	{
		ll_node *node = new ll_node(end);
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
		 head = previousPos;
	}

	void print()
	{
		ll_node *temp = head;
		while (temp != NULL)
		{
			cout << temp->val << " ";
			temp = temp->next;
		}
	}
};



int main(int argc, char *argv[])
{
	linked_list ll;
	ll.add(1);
	ll.add(2);
	ll.add(3);

	ll_node *node = ll.head;

	cout << "Given list" << endl;
	ll.print();
	cout << endl;
	ll.reversedList();
	cout << "Reverse list" << endl;
	ll.print();

	delete &ll;
	return 0;
}