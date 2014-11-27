#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"
#include <iostream>

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
    
    bool insertNode(TreeNode*& root, DBentry* newEntry);
    DBentry* findNode(TreeNode*& root, string name);
    void count(TreeNode*& root, int& activeCount) const;
    void clearAll(TreeNode*& root);
    bool removeNode(TreeNode*& root, string name);
    DBentry* findBiggestLeft(TreeNode*& root);
    
    void balance(TreeNode*& root);
    void rotateRight(TreeNode*& rootP);
    void rotateLeft(TreeNode*& rootQ);
    int balanceFactor(TreeNode*& root);
    int getHeight(TreeNode*& root);
    void fixHeight(TreeNode*& root);

public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   DBentry* find(string name);
   
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes() const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

   // Prints the entire tree, in ascending order of key/name
   friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

ostream& operator<< (ostream& out, TreeNode* rhs);
   
#endif 
