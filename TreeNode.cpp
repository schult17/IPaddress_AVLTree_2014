#include "TreeNode.h"

TreeNode::TreeNode()
{
    entryPtr = NULL;
    left = NULL;
    right = NULL;
    
    //AVL TREE
    left_w = 0;
    right_w = 0;
    height = 0;
}

TreeNode::TreeNode(DBentry* _entryPtr)
{
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode()
{
    delete entryPtr;
}

TreeNode* TreeNode::getLeft() const
{
    return left;
}

TreeNode* TreeNode::getRight() const
{
    return right;
}

DBentry* TreeNode::getEntry() const
{
    return entryPtr;
}

int TreeNode::gHeight()
{
    return height;
}

ostream& operator<< (ostream& out, TreeNode* rhs)
{
    if(rhs != NULL)
    {
        out << rhs->getLeft();
        out << *(rhs->getEntry()) << " : Height of node = " << rhs->gHeight() << endl;
        out << rhs->getRight();
        
        return out;
    }
    else
    {
        return out;
    }
}
