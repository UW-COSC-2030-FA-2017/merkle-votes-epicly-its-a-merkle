#ifndef PMT_H
#define PMT_H

#include "bTREE.h"
#include <string>
using namespace std;
class pMT
{
private:
    int selectedHash;
    bTREE myMerkle;
    
    string hash_1(string val);
    string hash_2(string val);
    string hash_3(string val);
    
public:
    pMT(int);
    ~pMT();
    
	string iToS(unsigned long long number);

	string hash(string val);

	bool changeHash(int hash);
    
    int insert(string vote, int time);
    
    int find(string val);
    int findHash(string val);
    
    string locate(string val);

	string locateHash(string mhash);

	void display();
    
	string getData(string location) const;

	void clearTree();

	bool isEmpty();

	string getRoot();
	
   friend bool operator==(const pMT& lhs, const pMT& rhs);
   
   friend bool operator!=(const pMT& lhs, const pMT& rhs);
    
   friend pMT operator^(const pMT& lhs, const pMT& rhs);
   friend std::ostream& operator<<(std::ostream& out, const pMT& p);
    
};

#endif
