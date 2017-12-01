#include "pMT.h"

/**
* @brief
* @param hashSelect a number corresponding to the hashfunction to use for this pMT
* @return
*/
pMT::pMT(int hashSelect)
{
	selectedHash = hashSelect;
}

/**
* @brief destructor
* @return nada
*/
pMT::~pMT()
{
}

// takes as a arguement a long long int and converts it into a string.
string pMT::iToS(unsigned long long number)
{
	string reversed;
	string rtn;
	int multiplier(10);
	long long digit;
	while (number != 0)
	{
		digit = number % multiplier;
		digit = (digit - (digit % (multiplier / 10)))/(multiplier/10);
		if (digit == 0)
		{
			reversed += '0';
		}
		else if (digit == 1)
		{
			reversed += '1';
		}
		else if (digit == 2)
		{
			reversed += '2';
		}
		else if (digit == 3)
		{
			reversed += '3';
		}
		else if (digit == 4)
		{
			reversed += '4';
		}
		else if (digit == 5)
		{
			reversed += '5';
		}
		else if (digit == 6)
		{
			reversed += '6';
		}
		else if (digit == 7)
		{
			reversed += '7';
		}
		else if (digit == 8)
		{
			reversed += '8';
		}
		else if (digit == 9)
		{
			reversed += '9';
		}
		else
		{
			reversed += 'E'; // E for error
		}
		number = number / multiplier;
	}
	for (int i = (reversed.size() - 1); i >= 0; i--)
	{
		rtn += reversed[i];
	}
	return rtn;
}

string pMT::hash(string val)
{
	if (selectedHash == 1)
	{
		return hash_1(val);
	}
	else if (selectedHash == 2)
	{
		return hash_2(val);
	}
	else
	{
		return hash_3(val);
	}
}

bool pMT::changeHash(int hash)
{
	if (myMerkle.isEmpty())
	{
		selectedHash = hash;
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief insert a vote and time into a leaf node of tree
* @param vote - a string
* @param time - an int representing the time
* @return the number of operations needed to do the insert, -1 if out of memory
*/
int pMT::insert(string vote, int time)
{
	string path = myMerkle.findShortestPath();


	if (path.size() == 0)
	{
		myMerkle.insert(vote, time);
	}
	else if (path[path.size() - 1] == '0')
	{
		myMerkle.insert(vote, time);
		path.pop_back();
		myMerkle.insert(myMerkle.getData(path), myMerkle.getTime(path));
		int size = path.size();

		for (int i = size; i >= 0; i--)
		{
			string right = path + '1';
			string left = path + '0';
			myMerkle.changeData(path, hash(myMerkle.getData(right) + myMerkle.getData(left)));
			if (path.size() > 0)
			{
				path.pop_back();
			}
		}
	}

	return 1;
}

/**
* @brief given a vote does this vote exist in the tree?
* @param vote, a string
* @param time, an int
* @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
* @return 0 if not found, else number of opperations required to find the matching vote
*/
int pMT::find(string vote)
{
	string tmp = myMerkle.locate(vote);
	return tmp.size();
}

/**
* @brief does this hash exist in the tree?
* @param mhash, a string to search for in the tree
* @return 0 if not found, else number of opperations required to find the matching hash
*/
int pMT::findHash(string mhash)
{
	return find(mhash);
}

/**
* @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
* @param vote, the data to search for
* @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
*/
string pMT::locate(string vote)
{
	string tmp = myMerkle.locate(vote);

	if (tmp.size() == 0)
	{
		return ".";
	}

	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] == '0')
		{
			tmp[i] = 'L';
		}
		else if(tmp[i] == '1')
		{
			tmp[i] = 'R';
		}
		else
		{
			return tmp;
		}
	}
	return tmp;
}

/**
* @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
* @param mhash, the hash to search for
* @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
*/
string pMT::locateHash(string mhash)
{
	return locate(mhash);
}

void pMT::display()
{
	myMerkle.display(cout);
}

string pMT::getData(string location) const
{
	return myMerkle.getData(location);
}

void pMT::clearTree()
{
	myMerkle.clear();
}

bool pMT::isEmpty()
{
	return myMerkle.isEmpty();
}

string pMT::getRoot()
{
	return myMerkle.getRoot();
}

/**
* @brief A function that takes in a key and returns a hash of that key using some custom function
* @param key, a string
* @return a hash of the key
*/
string pMT::hash_1(string key)
{
	/**
	* This hash is a somewhat smaller number. It uses two large prime numbers and multiplies them by
	* the asci value of the char, then adds them to a running sum.
	* There is no mudulo because this has relies on the overflow of the long long (if an overflow should occur).
	*/
	unsigned long long sum(0); //Sum begins at 0
	int multiplier1(4777463); //a very large prime number
	int multiplier2(1023557); //a very large prime number (numbers found on primes.utm.edu)
	int size = key.size(); // will add a value for everything in the string
	for (int i = 0; i < size; i++)
	{
		sum += key[i] * multiplier1; // add the character multiplied by the prime.
		sum += key[i] * multiplier2; // Add the same character multiplied by the other prime.
	}
	return iToS(sum); // Takes the int and converts it to a string for storage
}

/**
* @brief A function that takes in a key and returns a hash of that key using some custom function
* @param key, a string
* @return a hash of the key
*/
string pMT::hash_2(string key)
{
	/**
	* this function has the same premise as the last one, but it then multiples
	* the sum by 42 to make it larger. This hash was the first one to cause an overflow.
	* On my first iteration I used long long data type instead of unsigned long long
	* and thsi caused my results to be negative and outside of the range of my iToS function.
	* I solved this by making my data type unsigned long long and it immediately worked.
	* I also started the sum off at a six digit prime to seee if it would increase randomness.
	*/
	unsigned long long sum(680189); //sum begins at a big prime
	int multiplier1(4777463); // another big prime
	int multiplier2(1023557); // another big prime
	int size = key.size(); // end point of for loop
	for (int i = 0; i < size; i++)
	{
		sum += key[i] * multiplier1; // same as hash 1
		sum += key[i] * multiplier2; // same as hash 1
		sum = sum * 42; // the meaning of life.
	}
	return iToS(sum);
}

/**
* @brief A function that takes in a key and returns a hash of that key using some custom function
* @param key, a string
* @return a hash of the key
*/
string pMT::hash_3(string key)
{
	/**
	* This hash multiplies the sum by the key and by the multiplier.
	* if also does a modular by a large prime in the middle to try and increase the distribution 
	* of the numbers.
	*/
	unsigned long long sum(1); // sum must begin at 1 since everything is multiplication (learned this the hard way)
	int multiplier1(4777463); //big prime
	int multiplier2(1023557); //big prime
	int size = key.size();
	for (int i = 0; i < size; i++)
	{
		sum *= key[i] * multiplier1; // same as hash 2 except sum is multiplied instead of added to.
		sum = (sum % 2486784401); // mudulo a big prime to increase the distribution.
		sum *= key[i] * multiplier2; // multiply again
	}
	return iToS(sum);
}

bool operator==(const pMT & lhs, const pMT & rhs)
{
	if (lhs.myMerkle == rhs.myMerkle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief Comparison between two merkle trees
* @param lhs, the left hand side of the equality statment
* @param rhs, the right hand side of the equality statement
* @return true if not equal, false otherwise
*/
bool operator!=(const pMT & lhs, const pMT & rhs)
{
	return !(lhs == rhs);
}

/**
* @brief Where do two trees differ
* @param lhs
* @param rhs
* @return a tree comprised of the right hand side tree nodes that are different from the left
*/
pMT operator^(const pMT & lhs, const pMT & rhs)
{
	pMT* difference = new pMT(1);
	string path;

	if (rhs != lhs)
	{
		while (true)
		{
			if (rhs.getData(path + '0') != lhs.getData(path + '0'))
			{
				if (rhs.getData(path + '1') != lhs.getData(path + '1'))
				{
					difference->myMerkle.insert(rhs.getData(path), 1);
					string right(path + '1'), left(path + '0');
					difference->myMerkle.insert(rhs.getData(left), 1);
					difference->myMerkle.insert(rhs.getData(right), 1);
					difference->myMerkle.inorder(cout);
					break;
				}
				else
				{
					path = path + '0';
				}
			}
			else if (rhs.getData(path + '1') != lhs.getData(path + '1'))
			{
				path += '1';
			}
			else
			{
				difference->myMerkle.insert(rhs.getData(path), 1);
				break;
			}
		}
	}
	return *difference;
}

/**
* @brief Print out a tree
* @param out
* @param p
* @return a tree to the screen
*/
std::ostream & operator<<(std::ostream & out, const pMT & p)
{
	out << "Merkle Tree using hash " << p.selectedHash << ":" << endl;
	p.myMerkle.display(out);
	return out;
}
