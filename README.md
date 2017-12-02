# MerkleVotes

// Merkle tree by Chandler Haukap

Merkle Is Voting - And it's going to be epic.

This homework counts for your 4th 5th and 6th homeworks.

## Part One
1. Implement a binary tree (NOT a search tree)
2. Nodes must -
  * hold a pseudo-time stamp (integer, non-unique)[5]
  * hold a 128 bit data component (string of 32 characters)[5]
  * have 2 pointers to type node [5]
  * be differentiable if they are a leaf node or not [5]
3. A bTREE.h file and bTREE.cpp file are included but are incomplete
4. Complete the functions required [30]
  * Add any additional functions that might want

## Part Two
1. Use the binary tree created in part one to implement a pseudo-MerkleTree Class
2. Your Merkle Trees have some special properties:
  * Manually inserted data can only exist as leaf nodes
  * Non-Leaf nodes are the hashes of the child nodes below them
  * Our nodes should be ordered by a 'fake' time stamp
3. You must create at least 3 types of hash functions each group memeber is responsible for at least one
  * (they are listed at hash_1, hash_2 and hash_3).
4. pMT.h and pMT.cpp are provided but incomplete
5. Complete the functions provided [30]

### Individual Submission
1. Compute the number of operations it takes to:
  * Insert a new data node [4] 				//O(2)
  * Recompute hashes upon entry of a new node [4]	//O(h-1)
  * Compare if two trees are identical [4]			//O(1)
  *  Determine where two trees differ [4]			//O(h)
2. Describe your hash function in detail [4]

My hash functions (I made three) all use unsigned long long types which are then converted to strings. The long long is set to a begining value (0 for the first, a large 
prime for the second, and 1 for the third) then modified by adding to it the ascii value of each character multiplied by a large prime number. For my hashes the key is 
first multiplied by one large prime and then by another. This multiplication would overflow the long long data type allowing the physical boundary of the type to act 
as a modulo. for my second function I also multiplied the long long by 42 to see if it would  make a difference. This additional multiplication caused more overflows 
because it was performed afer the long long was getting  extremely large. In my last hash function (hash3) I multiplied the long long by both the acscii value and by the 
large primes. This created even more overflow which made the hashes more distributed.

The reason I used prime numbers is becasue they cannot be factored. Since the funtion is doing repeated multiplication a problem could arise if for example I used 64:
	(ascii value) * 64 =  (ascii value * 4)  * 16  The problem with this is that two different ascii values could map to the same value.
This could cause the results to converge. the primes ensure that there is no mistake as the hash is repeated.

One problem that I ran into was using long long verses unsigned long long. The long long data type would become negative which was a huge problem for my  int to string 
function. At first I tried to solve it by using a large prime as a modulo. This failed because the c language does not do modulo correctly for negative numbers. By definition 
a modulo remainder should always be positive but c languages will output a negative remainder. To remedy this I therefore had to switch all of my long longs to unsigned 
long longs.

My functions:
Hash1:
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
		sum += key[i] * multiplier1; // Add the character multiplied by the prime.
		sum += key[i] * multiplier2; // Add the same character multiplied by the other prime.
	}
	return iToS(sum); // Takes the int and converts it to a string for storage

Hash2:
	/**
	* this function has the same premise as the last one, but it then multiples
	* the sum by 42 to make it larger. This hash was the first one to cause an overflow.
	* On my first iteration I used long long data type instead of unsigned long long
	* and it caused my results to be negative and outside of the range of my iToS function.
	* I solved this by making my data type unsigned long long and it immediately worked.
	* I also started the sum off at a six digit prime to see if it would increase randomness.
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
Hash3:
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


Submit your answers on WyoCourses

## Part Three
1. Create a vote.cc with a main function that stores 'time stamped' votes into your pmTree data structure
2. Vote Data will be a string in the following format RANDOM:CANDIDATE
3. You will be provided with sample voterFiles.
4. Your program should be able to:
  * Read in a single file with timestamped votes and output the value of the root node 
  * Read in two sets of time stamped vote files, and:
  * If identical, print "Validated"
  * If not identical, print the sub-trees that differ, along with the offending vote data 

## Final Project (more details forthcoming)
Create a poster using the template provided, describing your design decisions, lessons learned, future extension ideas, ...
Poster will be due at the time of final code submission

You must change this readme file to contain the names of your group members as well as the mathematical functions you have each implemented for your hash functions.
