// Author: Michael Skarlatov
//Makes a stack using a linked list

#include "stdafx.h"
#include <iostream>
#include <string.h>
using namespace std;

//Node structre
struct node
{
	int val;
	node *next;
};
node *top;

//Stack class that makes the prototypes
class stack
{
public:
	void push(int n);
	void pop();
	void display();
};

//Push funciton which adds an inputed value to the stack
void stack::push(int n)
{
	struct node *newNode = new node;
	newNode->val = n;
	newNode->next = top;
	top = newNode;
}

//Pop function which removes the top of the stack
void stack::pop()
{
	if (top == NULL)
	{
		cout << "Empty" << endl;
		return;
	}
	cout << top->val << " was removed" << endl;
	top = top->next;
}

//Display function which prints out the stack
void stack::display()
{
	if (top == NULL)
	{
		cout << "Empty" << endl;
		return;
	}
	struct node *temp = top;
	while (temp != NULL)
	{
		cout << temp->val << " " << endl;
		temp = temp->next;
	}
	cout << endl;
}

//Main function
int main()
{
	//Makes a stack and other variables
	stack s;
	char ch;
	do
	{
		//User is asked to input a value for a function
		int choice;
		cout << "Please enter an option: \n1.Push\n2.Pop\n3.Display" << endl;
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		//Adds a users input to the stack
		case 1:
			node n;
			cout << "Enter and integer: ";
			cin >> n.val;
			std::cin.ignore(1);
			s.push(n.val);
			break;
		//Pops the top of the stack and tells the user what was removed
		case 2:
			s.pop();
			break;
		//Displays the stack
		case 3:
			cout << "The stack looks like:" << endl;
			s.display();
			break;
		//Default in case the user inputs a wrong input
		default:
			cout << "Invalid Choice" << endl;
		}
		//Asks the user if they would still like to use the program
		cout << "Do you wnat to continue? (Enter Y to continue or anything else to not continue)" << endl;
		cin >> ch;
	} while (toupper(ch) == 'Y');
    return 0;
}

