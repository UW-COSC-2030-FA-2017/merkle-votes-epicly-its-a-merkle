#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
}

bTREE::~bTREE()
{
}

int bTREE::dataInserted()
{
}

int bTREE::numberOfNodes()
{
    return numberOfNodes(head);
}

int bTREE::numberOfNodes(treeNode* tree_)
{
    if(tree_ == nullptr)
    {
        return 0;
    }
    else if(tree_->left_ != nullptr)
    {
        if(tree_->right_ != nullptr)
        {
            return (1 + numberOfNodes(tree_->right) + numberOfNodes(tree_->left_));
        }
        else
        {
            return (1 + numberOfNodes(tree_->left));
        }
    }
    else if(tree_->right_ != nullptr)
    {
        return (1 + numberOfNodes(tree_->right_));
    }
    else
    {
        return 1;
    }
}

bool bTREE::insert(string val, int time)
{
}

bool bTREE::find(string val)
{
    return find(string,val);
}

bool find(string val, treeNode* tree_)
{
    if(tree_->data == val)
    {
        return true;
    }
    else if(tree_->left_ != nullptr)
    {
        if(tree_->right != nullptr)
        {
            return (find(val,tree_->right_) || find(val,tree_->left_));
        }
        else
        {
            return (find(val,tree_->left_));
        }
    }
    else if(tree_->right_ != nullptr)
    {
        return (find(val,tree_->right));
    }
    else
    {
        return false;
    }
}

string bTREE::locate(string)
{
}

friend bool bTREE::operator ==(const bTREE& lhs, const bTREE& rhs)
{
}

friend bool bTREE::operator !=(const bTREE& lhs, const bTREE& rhs)
{
}

friend std::ostream& bTREE::operator <<(std::ostream& out, const bTREE& p)
{
}
