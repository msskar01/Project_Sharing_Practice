// Michael_Skarlatov_Nearest_Point.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

//Point class that creates points and can use functions using points
class Point
{
public:
	//Constructor for a point object using the point class
	Point(int a, int b) : x(a), y(b) 
	{}

	//Method that helps print a point
	void PrintPoint(Point p)
	{
		cout << "(" << p.x << "," << p.y << ")";
	}

	//Euclidean distance equation that takes two points and outouts the distance between them
	double Euclidean(Point p, Point q)
	{
		return (sqrt(pow(p.y - q.y, 2) + pow(p.x - q.x, 2)));
	}

	//Manhattan distance equation that takes two points and outouts the distance between them (this is not equal to euclidean)
	double Manhattan(Point p, Point q)
	{
		return (abs(p.y - q.y) + abs(p.x - q.y));
	}
	
	//Method that takes a vector of points and asks the user if they want to use euclidean or manhattan method to find the distance of the points 
	double CheckVector(vector<Point> points, int &position1, int &position2)
	{
		double distance = 0, minE = Euclidean(points[0], points[1]), minM = Manhattan(points[0], points[1]);
		char equation;
		cout << "Would you like to use the Euclidean or Manhattan distance equation to find the shortest distance between two points in the list" << endl;
		cin >> equation;
		//Loops that check the whole vector for all pairs of points and there distance
		for (int i = 0; i < points.size(); i++) 
		{
			for (int j = i+1; j < points.size(); j++)
			{
				if(tolower(equation) == 'e')
				{
					distance = Euclidean(points[i], points[j]);
					if (distance < minE)
					{
						minE = distance;
						position1 = i;
						position2 = j;
					}
				}
				else if (tolower(equation) == 'm')
				{
					distance = Manhattan(points[i], points[j]);
					if (distance < minM)
					{
						minM = distance;
						position1 = i;
						position2 = j;
					}
				}
				else
				{}
			}
		}
		if (tolower(equation) == 'e')
		{
			return minE;
		}
		else if (tolower(equation) == 'm')
		{
			return minM;
		}
	}

private:
	//x and y varibales used for point coordinates
	int x; 
	int y;
};

int main()
{
	//Variable creation
	int inputx, inputy, count = 0; 
	int postion1 = 0, position2 = 1;
	int choice = 1;
	double min = 0;
	vector<Point> points;
	Point p(0, 0);
	do
	{
		//User input of points
		cout << "Please enter in the x varibale of the point" << endl;
		cin >> inputx;
		cout << "Please enter in the y varibale of the point" << endl;
		cin >> inputy;
		Point newpoint(inputx, inputy);
		points.push_back(newpoint);
		if (count >= 1)
		{
			cout << "Would you like to add another point? (1 for yes or 2 for no): " << endl;
			cin >> choice;
		}
		count++;
	} while (choice == 1);

	min = p.CheckVector(points, postion1, position2);
	//Output value
	cout << "The min distance between the list of points is " << min << " between the points ";
	p.PrintPoint(points[postion1]);
	cout << " and ";
	p.PrintPoint(points[position2]);
    return 0;
}

