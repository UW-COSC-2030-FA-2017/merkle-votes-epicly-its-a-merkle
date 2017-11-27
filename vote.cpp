#include <stdio.h>
#include "bTREE.h"
#include <iostream>
#include "pMT.h"
using std::cout;
using std::endl;

void help();

int main(int argc, char **argv)
{
	cout << "...:::PSUEDO MERKLE TREE BY CHANDLER HAUKAP::..." << endl << "Enter 1, 2, or 3 to select a hash function:";
	int a(0);
	while (a != 1 && a != 2 && a != 3)
	{
		if (!(cin >> a))
		{
			cin.clear();
			cin.ignore();
			cout << endl << "Enter 1, 2 , or 3:";
		}
		else if (a != 1 && a != 2 && a != 3)
		{
			cout << endl << "Enter 1, 2 , or 3:";
		}
	}
	pMT test(a);

	int time(0);
	string entry("enter the loop");
	cout << endl << "Cast your vote! Enter a name then hit enter, or type 'done' to finish:" << endl;
	while (entry != "done" && entry != "Done" && entry != "DONE" && entry != "'done'")
	{
		cout << endl << "Name ('done' to finish): ";
		if (!(cin >> entry))
		{
			cout << endl << "Not a valid string." << endl;
			cin.clear();
			cin.ignore();
		}
		else if (entry != "done" && entry != "Done" && entry != "DONE" && entry != "'done'")
		{
			test.insert(entry, time);
			cout << endl << "Your vote has been cast!" << endl;
			time++;
		}
	}

	cout << endl << "Votes cast. What would you like to do next?";
	help();
	while (true)
	{
		break;
	}


	test.display();
	cout << endl << test.locate("syd");
	cout << endl << test.locate("Kyle");

	return 0;
}

void help()
{
	cout << endl << "search <Name>\t To locate a specific vote.";
	cout << endl << "display\t\t To display the tree graphically.";
	cout << endl << "inorder\t\t To do an inorder traversal of the tree.";
	cout << endl << "new\t\t To create a new merkle tree. (Stores 2 trees at a time)";
	cout << endl << "compare\t\t To compare the two stored trees.";
	cout << endl << "help\t\t to view comands." << endl;
}
