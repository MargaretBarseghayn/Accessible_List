// AccessibleList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"

int main()
{
	List lst;
	cout << endl << "*****   INSERTIONS: *****" << endl;
	lst.insert(1, 10); 
	lst.insert(1, 20);
	lst.insert(2, 30);
	lst.insert(4, 50);
	lst.insert(2, 60);
	lst.insert(4, 40);
	lst.print();
	
	cout << endl << "*****   REMOVAL IN 3-rd POSITION: *****" << endl;
	lst.remove(3);
	lst.print();

	cout << endl << "*****   REMOVAL IN 4-th POSITION: *****" << endl;
	lst.remove(4);
	lst.print();

	cout << endl << "*****   REMOVAL IN 1-st POSITION: *****" << endl;
	lst.remove(1);
	lst.print();

	return 0;
}

