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

struct linked_list
{
private:

public:
	ll_node * head;
	ll_node *tail;

	linked_list()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	void add(int end)
	{
		ll_node node(end);
		if (this->head == nullptr)
		{
			this->head = &node;
		}
		else
		{
			this->tail->next = &node;
		}
		this->tail = &node;
	}

};

int main(int argc, char *argv[])
{	
	linked_list ll;
	ll_node a(1);
	ll_node b(2);
	ll_node c(3);

	ll_node *node = ll.head;

	ll.head = &a;
	ll.tail = &c;
	a.next = &b;
	b.next = &c;

	cout << ll.head->next->next->val << endl;
	ll.pop_back();
	cout << ll.tail << endl;
	delete a, b, c;
	return 0;
}