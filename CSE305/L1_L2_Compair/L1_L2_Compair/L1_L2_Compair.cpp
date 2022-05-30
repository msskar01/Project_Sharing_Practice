// Author: Michael Skarlatov
//Procedure to compute L1 ∩L2 

#include "stdafx.h"
#include <list>

using namespace std;

//Intersection method that uses only basic list operations
list intersect(list L1, list L2)
{
	list result;
	position L1possition = first(L1), L2possition = first(L2), resultPossition = first(result);

	while (L1possition != NULL && L2possition != NULL)
	{
		//Checks to see which list element is larger to go through the next list
		if (L1possition->element < L2possition->element)
		{
			L1possition = L1possition->next;
		}
		else if (L1possition->element > L2possition->element)
		{
			L2possition = L2possition->next;
		}
		//Goes through both lists at the same time
		else
		{
			insert(L1possition->element, result, resultPossition);
			L1possition = L1possition->next;
			L2possition = L2possition->next;
			resultPossition = resultPossition->next;
		}
	}
	return result;
}
