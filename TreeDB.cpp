#include "TreeDB.h"

TreeDB::TreeDB()
{
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB()
{
    clear();
}

bool TreeDB::insert(DBentry* newEntry)
{
    return insertNode(root, newEntry);
}

bool TreeDB::insertNode(TreeNode*& root, DBentry* newEntry)
{
    if(root == NULL)
    {
        root = new TreeNode(newEntry);
        probesCount += 1;
    }
    else if(newEntry->getName() < (root->getEntry())->getName())
    {
        //don't return here, we want balance() to execute
        //for each root as the function stack pops
        insertNode(root->left, newEntry);
    }
    else if(newEntry->getName() > (root->getEntry())->getName())
    {
        //same here
        insertNode(root->right, newEntry);
    }
    else
    {
        //only if else case where we will return, we found a matching node
        //that already exists so delete dynamically created DBentry,
        //NULL the pointer, return false, no need to balance
        delete newEntry;
        newEntry = NULL;
        return false;
    }
    
    //upon the function returning, balance each node as we move back
    //up the tree and return true as we go (inserted)
    balance(root);
    return true;
}

DBentry* TreeDB::find(string name)
{
    probesCount = 0;
    return findNode(root, name);
}

DBentry* TreeDB::findNode(TreeNode*& root, string name)
{
    if(root != NULL)
    {
        //to track probes visited (multi use function)
        probesCount += 1;
        
        if(name < (root->getEntry())->getName())
        {
            return findNode(root->left, name);
        }
        else if(name > (root->getEntry())->getName())
        {
            return findNode(root->right, name);
        }
        else
        {
            return root->getEntry();
        }
        
    }
    else{return NULL;}
        
}

DBentry* TreeDB::findBiggestLeft(TreeNode*& root)
{
    if(root->right != NULL)
    {
        return findBiggestLeft(root->right);
    }
    else
    {
        return root->getEntry();
    }
}

bool TreeDB::remove(string name)
{
    return removeNode(root, name);
}

bool TreeDB::removeNode(TreeNode*& root, string name)
{
    if(root != NULL)
    {
        if(name < (root->getEntry())->getName())
        {
            //don't return here, we want balance() to execute
            //for each root as the function stack pops
            removeNode(root->left, name);
        }
        else if(name > (root->getEntry())->getName())
        {
            //same here
            removeNode(root->right, name);
        }
        else
        {
            TreeNode* delPtr = root;
            if(root->left == NULL && root->right == NULL)
            {
                delete delPtr;
                root = NULL;
            }
            else if(root->left != NULL && root->right == NULL)
            {
                root = root->left;
                delete delPtr;
            }
            else if (root->left == NULL && root->right != NULL)
            {
                root = root->right;
                delete delPtr;
            }
            else
            {
                DBentry* biggestLeft = findBiggestLeft(root->left);
                root->entryPtr = biggestLeft;
                removeNode(root->left, biggestLeft->getName());
            }
        }
        
        //balance the tree then return, if we are in this else block
        //we now we will be deleting so we can balance and return true
        balance(root);
        return true;
    }
    else
    {
        //no need to balance, just return false
        return false;
    }
}

void TreeDB::clear()
{
    clearAll(root);
}

void TreeDB::clearAll(TreeNode*& root)
{
    if(root != NULL)
    {
        clearAll(root->left);
        clearAll(root->right);
        delete root;
        root = NULL;
    }
}

void TreeDB::printProbes() const
{
    cout << probesCount << endl;
}

void TreeDB::countActive() const
{
    int activeCount = 0;
    
    TreeNode* temp_root = root;
    count(temp_root, activeCount);
    
    cout << activeCount << endl;
}

void TreeDB::count(TreeNode*& root, int& activeCount) const
{
    if(root != NULL)
    {
        if((root->getEntry())->getActive())
            activeCount += 1;
        
        count(root->left, activeCount);
        count(root->right, activeCount);
    }
}

ostream& operator<< (ostream& out, const TreeDB& rhs)
{
    out << rhs.root;
    return out;
}


/*****************AVL TREE ADDITION**********************/
int TreeDB::getHeight(TreeNode*& root)
{
    //if the pointer is NULL, return a height of 0
    return (root ? root->height : 0);
}

int TreeDB::balanceFactor(TreeNode*& root)
{
    //made right heavy positive, left heavy negative
    return (getHeight(root->right) - getHeight(root->left));
}

void TreeDB::fixHeight(TreeNode*& root)
{
    //get the height of the left and right subtrees
    int hl = getHeight(root->left);
    int hr = getHeight(root->right);
    
    //whatever height is greater, this tree is one more
    root->height = (hl > hr ? hl : hr) + 1;
}

void TreeDB::rotateRight(TreeNode*& rootP)
{
    //rotates the root to the right
    TreeNode* Q = rootP->left;
    rootP->left = Q->right;
    Q->right = rootP;
    
    //fixes the heights of the changed trees
    fixHeight(rootP);
    fixHeight(Q);
    
    //re assigns the root pointer (parent)
    rootP = Q;
}

void TreeDB::rotateLeft(TreeNode*& rootQ)
{
    //rotates the root to the left
    TreeNode* P = rootQ->right;
    rootQ->right = P->left;
    P->left = rootQ;
    
    //fixes the heights of the changed trees
    fixHeight(rootQ);
    fixHeight(P);
    
    //re assigns the root pointer (parent)
    rootQ = P;
}

void TreeDB::balance(TreeNode*& root)
{
    fixHeight(root);
 
    //by convention, we are right heavy
    if(balanceFactor(root) == 2)
    {
        //if we have a zig-zag form, we must rotate right then left
        if(balanceFactor(root->right) < 0)
        {
            cout << "rebalancing..." << endl;
            rotateRight(root->right);
        }
        
        //if we have a linked list form, we only need to rotate left,
        //if we had a zig zag form, we already rotated right, now left
        cout << "rebalancing..." << endl;
        rotateLeft(root);
    }
    else if(balanceFactor(root) == -2)     //left heavy
    {
        //if we have a zig-zag form, we must rotate left then right
        if(balanceFactor(root->left) > 0)
        {
            cout << "rebalancing..." << endl;
            rotateLeft(root->left);
        }
        
        //if we have a linked list form, we only need to rotate right,
        //if we had a zig zag form, we already rotated left, now right
        cout << "rebalancing..." << endl;
        rotateRight(root);
    }
}
