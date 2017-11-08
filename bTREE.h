#pragma once
#include <string>
using namespace std;

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

public:
    bTREE();
    ~bTREE();

    int dataInserted();
    int numberOfNodes();

    bool insert(string, int);

    bool find(string val);

    string locate(string);


    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);

};

