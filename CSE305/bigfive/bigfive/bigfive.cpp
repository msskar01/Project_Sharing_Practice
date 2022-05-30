#include "stdafx.h"
#include <iostream>
using namespace std;
#define CONSTRUCTOR 
#define DECONSTRUCTOR
#define DEBUG

class IntCell
{
public:
#ifdef CONSTRUCTOR 
	IntCell(int initialValue = 0)
	{
#ifdef DEBUG
		cout << "Constructor" << endl;
#endif
		storedValue = new int{ initialValue };
	}
#endif	
#ifdef COPYCONSTRUCTOR 
	//copy constructor
	IntCell(const IntCell& rhs)
	{
#ifdef DEBUG
		cout << "Copy Constructor" << endl;
#endif
		storedValue = new int{ *rhs.storedValue };
	}
#endif
#ifdef DECONSTRUCTOR
	//delete construcor
	~IntCell() {
#ifdef DEBUG
		cout << "deConstructor" << endl;
#endif
		delete storedValue;
	}
#endif
#ifdef MOVECONSTRUCTOR
	//move constructor
	IntCell(IntCell&& rhs) : storedValue{ rhs.storedValue }
	{
#ifdef DEBUG
		cout << "Move Constructor" << endl;
#endif
		rhs.storedValue = nullptr;
	}
#endif
#ifdef COPYASSIGNMENT
	//Copy assignment 
	IntCell & operator=  (const IntCell &rhs) {
#ifdef DEBUG
		cout << "Copy Assignment" << endl;
#endif
		if (this != &rhs)
			*storedValue = *rhs.storedValue;
		return *this;
	}
#endif
#ifdef MOVEASSIGNMENT
	//Move assignment 

	IntCell & operator=  (IntCell &&rhs) {
#ifdef DEBUG
		cout << "Move Assignment" << endl;
#endif
		swap(storedValue, rhs.storedValue);
		return *this;
	}
#endif
	int read()    const
	{
		return *storedValue;
	}
	void write(int x)
	{
		*storedValue = x;
	}

private:
	int *storedValue;
};
int main()
{
	IntCell m(21), n(11);
	cout << "Cell contents: " << m.read() << endl;
	cout << "Cell contents: " << n.read() << endl;

	n = m;
	cout << "Cell contents: " << m.read() << endl;
	cout << "Cell contents: " << n.read() << endl;

	m.write(15);
	cout << "Cell contents: " << m.read() << endl;
	cout << "Cell contents: " << n.read() << endl;

	cout << "107 JB speed" << endl;

	return 0;
}