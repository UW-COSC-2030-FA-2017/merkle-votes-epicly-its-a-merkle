#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	head = nullptr;
}

bTREE::~bTREE()
{
	if (head != nullptr)
	{
		deleteNode(head);
	}
}

// NEEDS documentation
int bTREE::dataInserted()
{
	return dataInserted(head);
}

//returns size of the tree
int bTREE::numberOfNodes()
{
    return numberOfNodes(head);
}

//returns size of the tree
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

// returns the location of the data as a string of binary digits
// using the convention described in findShortestPath()
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

/*
Returns the shortest path as a string of 0s and 1s. 
0  represents "go left" and 1 represents "go right" like
a text compression document.
*/
string bTREE::findShortestPath(treeNode * tree_)
{
	// a comparison must be made since there are multiple branches.
	string left;
	string right;

	//If the tree is empty.
	if (tree_ == nullptr)
	{
		return "";
	}
	else if (tree_->left_ != nullptr) // if left has content.
	{
		if (tree_->right_ != nullptr) // and right has content.
		{
			left = ('0' + findShortestPath(tree_->left_)); // assume we go left, then find the path from there.
			right = ('1' + findShortestPath(tree_->right_)); // assumer we go right, then find the path from there.
			if (left.size() > right.size()) // since every bit represents a step, the path with the fewest steps is the shortest.
			{
				return right;
			}
			else
			{
				return left;
			}
		}
		else // if left has content but right does not.
		{
			return "1"; //go right
		}
	}
	else //if left has no content end recursion and go here
	{
		return "0"; // this ensures that left fills before right.
	}
}

// Inserts Node at the location of the shortest path.
// fills every level before moving to the next.
// Preference for left nodes before right.
bool bTREE::insert(string val, int time, treeNode* &tree_)
{
	treeNode* insertion = new treeNode;
	insertion->data = val;
	insertion->time = time;
	insertion->left_ = nullptr;
	insertion->right_ = nullptr;

	// If head is null.
	if (tree_ == nullptr)
	{
		tree_ = insertion;
		return true;
	}

	// parent will move to the location of the parent node which will recieve the child.
	treeNode* parent = tree_;

	// assigns a binary string to at.
	string at = findShortestPath();

	for (int i = 0; i < (at.size() - 1); i++) // move parent throught the tree to the location of the opening
	{
		if (at[i] == '0') // go left
		{
			parent = parent->left_;
		}
		else if (at[i] == '1') // go right
		{
			parent = parent->right_;
		}
	}

	// parent is in position.
	// now decides if it should add to the right branch or the left branch.
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

// inorder traversal of the tree.
void bTREE::inorder(vector<string>& traversal, treeNode * tree_)
{
	if (tree_ != nullptr)
	{
		inorder(traversal, tree_->left_);
		traversal.push_back(tree_->data);
		inorder(traversal, tree_->right_);
	}
}

// Display functions modified from "BinaryTree.h" by Tom Bailey.
// Used for testing purposes and to visualize the tree. 
// Displays the tree in inorder notation with 'left' being the top
// and 'right' being the bottom.
void bTREE::display(std::ostream& outfile) const
{
	std::string prefix;
	if (head == NULL)
	{
		outfile << "-" << std::endl;
	}
	else
	{
		displayLeft(outfile, head->right_, "       ");
		outfile << "---" << head->data << std::endl;
		displayRight(outfile, head->left_, "       ");
	}
}


// Display functions modified from "BinaryTree.h" by Tom Bailey.
// Used in lab 8.
void bTREE::displayLeft(std::ostream & outfile, treeNode * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "/" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->right_, prefix + "        ");
		outfile << prefix + "/---" << subtree->data << std::endl;
		displayRight(outfile, subtree->left_, prefix + "|       ");
	}
}

void bTREE::deleteNode(treeNode * thisNode)
{
	if (thisNode->left_ != nullptr)
	{
		deleteNode(thisNode->left_);
	}
	if (thisNode->right_ != nullptr)
	{
		deleteNode(thisNode->right_);
	}
	delete thisNode;
}

int bTREE::dataInserted(treeNode * thisNode)
{
	if (thisNode == nullptr)
	{
		return 0;
	}
	else if (thisNode->left_ != nullptr)
	{
		if (thisNode->right_ != nullptr)
		{
			return (dataInserted(thisNode->left_) + dataInserted(thisNode->right_));
		}
		return dataInserted(thisNode->left_);
	}
	else if (thisNode->right_ != nullptr)
	{
		return dataInserted(thisNode->right_);
	}
	else
	{
		return 1;
	}
}

bool bTREE::compareValues(treeNode * lhs, treeNode * rhs)
{
	if (lhs == nullptr && rhs == nullptr)
	{
		return true;
	}
	else if ((lhs == nullptr && rhs != nullptr) || (rhs == nullptr && lhs != nullptr))
	{
		return false;
	}
	else if (lhs->data != rhs->data || rhs->time != lhs->time)
	{
		return false;
	}
	else
	{
		return (compareValues(lhs->right_, rhs->right_) && compareValues(lhs->left_, rhs->left_));
	}

}

// Modified from code by Tom Bailey.
void bTREE::displayRight(std::ostream & outfile, treeNode * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "\\" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->right_, prefix + "|       ");
		outfile << prefix + "\\---" << subtree->data << std::endl;
		displayRight(outfile, subtree->left_, prefix + "        ");
	}
}

// inserts value into tree in left-to-right order.
bool bTREE::insert(string val, int time)
{
	return insert(val, time, head);
}

//returns true the value is in the tree. false otherwise.
bool bTREE::find(string val)
{
    return find(val,head);
}

//prints and inorder traversal of the tree.
void bTREE::inorder()
{
	vector<string> trav;
	inorder(trav, head);
	for (int i = 0; i < trav.size(); i++)
	{
		cout << trav[i] << " ";
	}
}

// Locates the data and returns true if it was located.
bool bTREE::find(string val, treeNode* tree_)
{
	if (tree_ == nullptr)
	{
		return false;
	}
	else
	{
		if (tree_->data == val) //if the head contains the data
		{
			return true;
		}
		else if (tree_->left_ != nullptr) // if we can go left
		{
			if (tree_->right_ != nullptr) //if we can go left
			{
				return (find(val, tree_->right_) || find(val, tree_->left_)); //if either have the data then return true
			}
			else
			{
				return (find(val, tree_->left_)); // locate the data in the left branch
			}
		}
		else if (tree_->right_ != nullptr) //if right has data but left does not
		{
			return (find(val, tree_->right_)); // locate the data in the right branch
		}
		else
		{
			return false; // the end of the tree and the data was not found.
		}
	}
}

// returns the string describing the data's location.
string bTREE::locate(string val)
{
	return locate(val, head);
}

//returns string describing shortest path.
string bTREE::findShortestPath()
{
	return findShortestPath(head);
}

bool operator==(const bTREE & lhs, const bTREE & rhs)
{
	bTREE tmp;
	return tmp.compareValues(lhs.head, rhs.head);

	return false;
}

bool operator!=(const bTREE & lhs, const bTREE & rhs)
{
	bTREE tmp;
	return !tmp.compareValues(lhs.head, rhs.head);
}

std::ostream & operator<<(std::ostream & out, const bTREE & p)
{
	p.display(out);
	return out;
}
