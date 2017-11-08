#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	head = new treeNode;
	head->left_ = nullptr;
	head->right_ = nullptr;
}

bTREE::~bTREE()
{
}

int bTREE::dataInserted()
{
	return -1;
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
            return (1 + numberOfNodes(tree_->right_) + numberOfNodes(tree_->left_));
        }
        else
        {
            return (1 + numberOfNodes(tree_->left_));
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

string bTREE::locate(string val, treeNode * tree_)
{
	if (tree_->data == val) //If this is the data node, end recursion.
	{
		return "";
	}
	else if (find(val, tree_->right_)) //if we need to go right to find the string
	{
		return ('1' + locate(val,tree_->right_)); //concatenate 1 to signify 'go right'
	}
	else if (find(val, tree_->left_)) 
	{
		return ('0' + locate(val, tree_->left_)); //concatenate 0 to signify 'go left'
	}
	else
	{
		return "Data could not be found."; // not very efficient for trees that do not contain the data since it has to run 3 checks,									
	}									  // but we're assuming the user knows that what they are looking for exists.
}

string bTREE::findShortestPath(treeNode * tree_)
{
	string left;
	string right;
	if (tree_ == nullptr)
	{
		return "";
	}
	else if (tree_->right_ != nullptr)
	{
		if (tree_->left_ != nullptr)
		{
			left = ('0' + findShortestPath(tree_->left_));
			right = ('1' + findShortestPath(tree_->right_));
			if (left.size() > right.size())
			{
				return right;
			}
			else
			{
				return left;
			}
		}
		else
		{
			return "0";
		}
	}
	else
	{
		return "1";
	}
}

bool bTREE::insert(string val, int time, treeNode * tree_)
{
	treeNode* insertion = new treeNode;
	insertion->data = val;
	insertion->time = time;
	insertion->left_ = nullptr;
	insertion->right_ = nullptr;

	if (tree_ == nullptr)
	{
		tree_ = insertion;
		return true;
	}

	treeNode* parent = tree_;

	string at = findShortestPath();

	for (int i = 0; i < (at.size() - 1); i++)
	{
		if (at[i] == '0')
		{
			parent = parent->left_;
		}
		else if (at[i] == '1')
		{
			parent = parent->right_;
		}
	}

	if (at[at.size() - 1] == '0')
	{
		parent->left_ = insertion;
	}
	else
	{
		parent->right_ = insertion;
	}
	return true;
}

void bTREE::inorder(treeNode * tree_)
{
	if (tree_ != nullptr)
	{
		inorder(tree_->left_);
		display(tree_->right_);
		inorder(tree_->left_);
	}
}

void bTREE::display(treeNode * tree_)
{
	cout << tree_->data << " ";
}

bool bTREE::insert(string val, int time)
{
	return insert(val, time, head);
}

bool bTREE::find(string val)
{
    return find(val,head);
}

void bTREE::inorder()
{
	inorder(head);
}

bool bTREE::find(string val, treeNode* tree_)
{
    if(tree_->data == val)
    {
        return true;
    }
    else if(tree_->left_ != nullptr)
    {
        if(tree_->right_ != nullptr)
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
        return (find(val,tree_->right_));
    }
    else
    {
        return false;
    }
}

string bTREE::locate(string val)
{
	return locate(val, head);
}

string bTREE::findShortestPath()
{
	return findShortestPath(head);
}

/*
friend bool bTREE::operator ==(const bTREE& lhs, const bTREE& rhs)
{
}

friend bool bTREE::operator !=(const bTREE& lhs, const bTREE& rhs)
{
}

friend std::ostream& bTREE::operator <<(std::ostream& out, const bTREE& p)
{
}
*/
