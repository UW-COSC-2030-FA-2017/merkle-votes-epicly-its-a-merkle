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
	bool insert(string val, int time, treeNode* &tree_);
	void inorder(vector<string> &traversal, treeNode* tree_);

	static void displayRight(std::ostream & outfile,
		treeNode * subtree, std::string prefix);

	static void displayLeft(std::ostream & outfile,
		treeNode * subtree, std::string prefix);

public:
    bTREE();
    ~bTREE();

    int dataInserted();
    int numberOfNodes();

    bool insert(string val, int time);

    bool find(string val);

	void inorder();

    string locate(string val);

	string findShortestPath();

	void display(std::ostream& outfile) const;


	/*
    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);
	*/
};

