#ifndef _TREENODE_H
#define _TREENODE_H

#include "DBentry.h"
#include <iostream>

using namespace std;

class TreeNode {
private:
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right;
    
    /***AVL TREE***/
    int left_w;
    int right_w;
    int height;

public:
    // A useful constructor
    TreeNode(DBentry* _entryPtr);
    
    TreeNode();

    // the destructor
    ~TreeNode();

    // gets the left child of the TreeNode.
    TreeNode* getLeft() const;

    // gets the right child of the TreeNode
    TreeNode* getRight() const;

    // returns a pointer to the DBentry the TreeNode contains. 
    DBentry* getEntry() const;
    
    int gHeight();
    
    friend class TreeDB;
};

#endif 
