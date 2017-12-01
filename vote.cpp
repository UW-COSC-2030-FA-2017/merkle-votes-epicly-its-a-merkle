#include <stdio.h>
#include "bTREE.h"
#include <iostream>
#include <fstream>
#include "pMT.h"
using std::ifstream;
using std::cout;
using std::endl;

// Param: Tree to be operated on, string of the file name.
// operation: insert each line of the file into a merkle tree.
void read(pMT& tree, string fileName);

bool readToTree1(true); // Alternates the tree that the input file will be read to.

// Param: string of decimal values
// return: int version of the same value
int strToDec(string number);

int main(int argc, char **argv)
{
	cout << "...:::PSUEDO MERKLE TREE BY CHANDLER HAUKAP::..." << endl << endl;
	cout << "This program can store 2 trees at a time." << endl;
	cout << "Type 'read' to read in a tree and output the value of the root node." << endl;
	cout << "Type 'compare' to compare two trees that have been read in." << endl;
	cout << "Type 'display' to display the two trees." << endl;
	cout << "Type 'xor' to show the difference between tree one and tree two" << endl;
	cout << "Type 'end' to end the program." << endl;

	pMT tree1(2);
	pMT tree2(2);

	while (true)
	{
		cout << endl << "Enter command: ";
		string command;
		getline(cin, command);

		if (command == "read")
		{
			string name;
			cout << "Enter the name of the file to read: ";
			cin >> name;
			if (readToTree1)
			{
				if (!tree1.isEmpty())
				{
					tree1.clearTree();
				}
				read(tree1, name);
				cout << "Root Node: " << tree1.getRoot() << endl;
			}
			else
			{
				if (!tree2.isEmpty())
				{
					tree2.clearTree();
				}
				read(tree2, name);
				cout << "Root Node: " << tree2.getRoot() << endl;
			}
			cin.ignore();
		}
		else if (command == "compare")
		{
			if (tree1.isEmpty())
			{
				if (tree2.isEmpty())
				{
					cout << "Validated" << endl << "Warning: trees validated because they are both empty." << endl;
				}
				else
				{
					cout << "Not Validated" << endl << "Warning: tree 1 is empty." << endl;
				}
			}
			else if (tree2.isEmpty())
			{
				cout << "Not Validated" << endl << "Warning: tree 2 is empty." << endl;
			}
			else
			{
				if (tree1 == tree2)
				{
					cout << "Validated" << endl;
				}
				else
				{
					cout << "Not Validated" << endl;
				}
			}
		}
		else if (command == "end")
		{
			break;
		}
		else if (command == "display")
		{
			cout << "Tree 1:" << endl << tree1 << endl;
			cout << "Tree 2:" << endl << tree2 << endl;
		}
		else if (command == "xor")
		{
			pMT tree3 = tree1^tree2;
			cout << tree3;
		}
		else
		{
			cout << "Command not recognised. Type 'read', 'compare', 'xor', or 'end'" << endl << endl;
		}
	}

	return 0;
}

void read(pMT & tree, string fileName)
{
	ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		cout << "File could not be opened." << endl;
		return;
	}
	else
	{
		readToTree1 = !readToTree1; //Every time a file is read it will be put into an alternating tree.
		string tmp;
		string candidate;
		string time;
		if (!inFile.eof())
		{
			getline(inFile, tmp);  //Get the header line with description
		}

		while (!inFile.eof())
		{
			tmp.clear();
			getline(inFile, tmp);
			if (tmp.size() != 0)
			{
				candidate.clear();
				int loc(0);
				while (tmp[loc] != '\t')
				{
					candidate += tmp[loc];
					loc++;
				}
				loc++;

				while (loc < (tmp.size()))
				{
					time += tmp[loc];
					loc++;
				}

				int t = strToDec(time);
				tree.insert(candidate, t);
			}
		}
		cout << endl << "File successfully read!" << endl;
	}
}

/**
* Convert string to decimal. I couldn't get the std function to work and this wasn't
* too hard to write.
* '1'-'9' mapped to 1-9 and everything else mapped to 0.
*/
int strToDec(string number)
{
	int decimal(0), multiplier(1); // multiplier responsible for incrementing the decimal place.
	while (number.size() > 0) // keep doing this until the number variable is empty
	{
		char current = number[number.size() - 1]; // operate on char becasue it is easier.
		if (current == '1') // each possible number
		{
			decimal += 1 * multiplier; // will either add 1, 10, 100 ect.
		}
		else if (current == '2')
		{
			decimal += 2 * multiplier;
		}
		else if (current == '3')
		{
			decimal += 3 * multiplier;
		}
		else if (current == '4')
		{
			decimal += 4 * multiplier;
		}
		else if (current == '5')
		{
			decimal += 5 * multiplier;
		}
		else if (current == '6')
		{
			decimal += 6 * multiplier;
		}
		else if (current == '7')
		{
			decimal += 7 * multiplier;
		}
		else if (current == '8')
		{ 
			decimal += 8 * multiplier;
		}
		else if (current == '9')
		{
			decimal += 9 * multiplier;
		}
		number.pop_back(); // remove the last element (opperates from back-to-front because the multiplier increases.
		multiplier = multiplier * 10; // increment the location (base 10).
	}
	return decimal;
}


