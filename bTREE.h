#pragma once
#include <string>
using std::string;
#include <iostream>
using std::cout;
#include<vector>
using std::vector;

class bTREE
{
    struct treeNode{
        string data;
        int time;
        treeNode* right_;
        treeNode* left_;
        bool leaf;
    };

private:
    treeNode* head;
    bool find(string val, treeNode* tree_);
    int numberOfNodes(treeNode* tree_);
	string locate(string val, treeNode* tree_);
	string findShortestPath(treeNode* tree_);
	int insert(string val, int time, treeNode* &tree_);
	void inorder(std::ostream& out, vector<string> &traversal, treeNode* tree_) const;

	static void displayRight(std::ostream & outfile,
		treeNode * subtree, std::string prefix);

	static void displayLeft(std::ostream & outfile,
		treeNode * subtree, std::string prefix);

	void deleteNode(treeNode* thisNode);

	int dataInserted(treeNode* thisNode);

	bool compareValues(treeNode* lhs, treeNode* rhs);


public:
    bTREE();
    ~bTREE();

	// returns the number of leaf nodes.
    int dataInserted();

	// returns the total number of nodes.
    int numberOfNodes();

	// returns the data stored in a specific node.
	string getData(treeNode* node) const;

	//returns the data stored in a node.
	//param: location of node.
	string getData(string location) const;

	//returns the time stored in a node.
	//param: location of node.
	int getTime(string location);

	// inserts data into the shortest path 
    int insert(string val, int time);

	// returns true if the string is in the tree.
	// false otherwise.
    bool find(string val);

	// inorder traversal of the tree.
	void inorder(std::ostream& out) const;

	// param: string
	// return: location of that string in the tree.
    string locate(string val);

	//find the shortes path(where the next node should be inserted)
	//returns a string of 0 s and 1s. (0 for left and 1 for right)
	string findShortestPath();

	//display the tree graphically
	void display(std::ostream& outfile) const;

	//returns true if the heal is null, false else
	bool isEmpty();

	//clear all data from the tree.
	void clear();

	bool changeData(string location, string val);

	//returns the data stored in the head node.
	string getRoot();
	
    friend bool operator ==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);
    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);

};