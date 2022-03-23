#include "DSW_BST.h"
#include "customErrorClass.h"
#include <iomanip>
#include <math.h>

 C_DSW_BST::C_DSW_BST()
{
    this->p_holdArray = NULL;
}
C_DSW_BST::~C_DSW_BST()
{
    delete[] this->p_holdArray;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        sends the root, newNode into the p_insertValue function
**    Function Output: nothing
**    Side Effects: The exception could happen if there is a negative number inputed
*/
void C_DSW_BST::insertValue(S_NODE*& root, S_NODE* newNode)
{
    if(newNode->holdValue < 0)
    {
        throw MyException("Warning values entered are not valid.");
    }
    else
    {
        try
        {
            this->p_insertValue(root, newNode);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for finding a node
**    Function Output: nothing
**    Side Effects: exception for if a value is NULL then you cannot find a node
*/
void C_DSW_BST::findNode(S_NODE* root, int treeNum)
{
    if(treeNum == NULL)
    {
        throw MyException("This value is not accepted.");
    }
    else
    {
        try
        {
            this->p_findNode(root, treeNum);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for printing a tree
**    Function Output: none
**    Side Effects: exception if the root is empty, then cannot print anything
*/
void C_DSW_BST::printTree(S_NODE*& root, int indent)
{
    if(root == NULL)
    {
        throw MyException("The root is empty, cannot print.");
    }
    else
    {
        try
        {
            this->p_printTree(root, indent);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for sorting the tree after rotations
**    Function Output: none
**    Side Effects: exception if there arent enough nodes to sort
*/
void C_DSW_BST::sortTree(int countNode, S_NODE* root)
{
    if(countNode < 1)
    {
        throw MyException("Not enough nodes please add more.");
    }
    else
    {
        try
        {
            this->p_sortTree(countNode, root);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for height of nodes
**    Function Output: none
**    Side Effects: exception thrown if the root is empty, then cannot get a height 
*/
int C_DSW_BST::getHeight(S_NODE* root)
{
    if(root == NULL)
    {
        throw MyException("The tree's root is empty, please try again.");
    }
    else
    {
        try
        {
            return this->p_getHeight(root);
            
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for deleting the tree
**    Function Output: none
**    Side Effects: exception if there is no tree
*/
void C_DSW_BST::deleteTree(S_NODE* root)
{
    if(root == NULL)
    {
        throw MyException("The tree's root is empty, please try again.");
    }
    else
    {
        try
        {
            this->p_deleteTree(root);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for creating the nodes
**    Function Output: none
**    Side Effects: the excpetion throws if the tree is empty
*/
void C_DSW_BST::createVine(S_NODE* root)
{
    
    if(root == NULL)
    {
        throw MyException("The tree's root is empty, please try again.");
    }
    else
    {
        try
        {
            this->p_createVine(root);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for right rotation of the tree
**    Function Output: none
**    Side Effects: exception thrown if the left child is empty then cannot do rotation
*/
void C_DSW_BST::rotateRight(S_NODE* newNode)
{
    if(newNode->leftChild == NULL)
    {
        throw MyException("This nodes left child is empty, please try again.");
    }
    else
    {
        try
        {
            this->p_rotateRight(newNode);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for left rotation
**    Function Output: none
**    Side Effects: exception thrown if right child is empty then you cannot do left rotation
*/
void C_DSW_BST::rotateLeft(S_NODE* newNode)
{
    if(newNode->rightChild == NULL)
    {
        throw MyException("This nodes right child is empty, please try again.");
    }
    else
    {
        try
        {
            this->p_rotateLeft(newNode);;
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
    
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        
**    Function Output: 
**    Side Effects: 
*/
void C_DSW_BST::createTree()
{
    this->p_createTree();
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        this creates the right leaning vine of for all the nodes in order
**    Function Output: none
**    Side Effects: calls sort tree function which will balance the tree
*/
void C_DSW_BST::p_createVine(S_NODE* root)
{
    int countNode = 0;

    S_NODE* tempNode = root;
    
    
    while(tempNode != NULL)
    {
        while(tempNode->leftChild != NULL)
        {
            this->p_rotateRight(tempNode);
        }
        tempNode = tempNode->rightChild;
        
        countNode++;
    }
    
    
    this->sortTree(countNode, root);
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        rotates the node to the right
**    Function Output: none
**    Side Effects: will rotate the node passed through to the right influencing its children
*/
void C_DSW_BST::p_rotateRight(S_NODE* newNode)
{
    
    
    if(newNode->leftChild == NULL)
    {
        return;
    }
    int holdOgNumber1 = 0;
    S_NODE* holdleftChild;
    

    
    holdOgNumber1 = newNode->holdValue;//copy value of newNode
    holdleftChild = newNode->leftChild;//copy node right of og
    //switch values between og child and right child
    newNode->holdValue = holdleftChild->holdValue;
    newNode->leftChild->holdValue = holdOgNumber1;

    
    newNode->leftChild = holdleftChild->leftChild;//make the left child of left child the new left child
    
    holdleftChild->leftChild = holdleftChild->rightChild;//make the right child of the left child the new left child
    
    holdleftChild->rightChild = newNode->rightChild;//because we're swapping here, need to bring the orginial right child back to the original node
    
    newNode->rightChild = holdleftChild;//makes the hold of the left child the new right child
    
    
    
    

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        rotate the node and it's children to the left, backwards of right rotate
**    Function Output: none
**    Side Effects: the rotation will affect the nodes children and reconfigure tree
*/
void C_DSW_BST::p_rotateLeft(S_NODE* newNode)
{
    if(newNode->rightChild == NULL)
    {
        return;
    }
    int holdOgNumber = 0;
    S_NODE* holdRightChild;
    
    
    holdOgNumber = newNode->holdValue;//copy value of newNode
    holdRightChild = newNode->rightChild;//copy node right of og

    //switch values between og child and right child
    newNode->holdValue = holdRightChild->holdValue;
    newNode->rightChild->holdValue = holdOgNumber;

    newNode->rightChild = holdRightChild->rightChild;//make the right child of right child the new right child
    holdRightChild->rightChild = holdRightChild->leftChild;//make the left child of the right child the new right child
    holdRightChild->leftChild = newNode->leftChild;//because we're swapping here, need to bring the orginial left child back to the original node

    newNode->leftChild = holdRightChild;//makes the hold of the right child the new left child
    
    
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        
**    Function Output: 
**    Side Effects: 
*/
void C_DSW_BST::p_createTree()
{

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        puts values into the node after they created
**    Function Output: none
**    Side Effects: will put each proceeding node in either the left or right child depending on their value
*/
void C_DSW_BST::p_insertValue(S_NODE*& root, S_NODE* newNode)
{
    
    if(root == NULL)
    {
        root = newNode;
        
    }
    else if (newNode->holdValue < root->holdValue)
    {
        this->p_insertValue(root->leftChild, newNode);
        
    }
    else
    {  
        this->p_insertValue(root->rightChild, newNode);
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        finds a node corresponding to the value it was given
**    Function Output: the node that it was searching for
**    Side Effects: will return the root it found
*/
S_NODE* C_DSW_BST::p_findNode(S_NODE* root, int treeNum)
{
    if(root->holdValue == treeNum || root == NULL)
    {
            cout << "Found" << endl;
            return root;
    }
    else
    {
        if(root->holdValue < treeNum)
        {
            this->p_findNode(root->rightChild, treeNum);
        }
        if(root->holdValue > treeNum)
        {
            this->p_findNode(root->leftChild, treeNum);
        }
        
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        prints the tree once as a BST and once as a DSW balanced tree
**    Function Output: prints to the screen the node values 
**    Side Effects: none
*/
void C_DSW_BST::p_printTree(S_NODE* root, int indent)
{
   if(NULL == root)
    {
        return;
    }
    else
    {
        this->p_printTree(root->leftChild, indent+4);
        if( indent )
        {
            cout<<setw(indent)<< " ";
        }
        cout << root->holdValue<<endl;
        this->p_printTree(root->rightChild, indent+4);
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Sorts the tree in the DSW balance
**    Function Output: none
**    Side Effects: changes the tree's structure to be DSW balanced
*/
void C_DSW_BST::p_sortTree(int countNode, S_NODE* root)
{
    
    
    int countRot = countNode - (pow(2, floor(log2(countNode+1)))) ;
    //int remainRot = floor(p_treeHeight/2);
    
    S_NODE* tempNode = root;
    S_NODE* newTempNode = root;
    
    

    for(int i = 0; i < countRot; i++)
    {
        
        this->p_rotateLeft(tempNode->rightChild);
        tempNode = tempNode->rightChild;
        
    }
    

    int remainRot = 16;
    
    
    while(remainRot > 1)
    {
       
        remainRot /= 2;
        
        for(int count = 0; count < remainRot-1; count++)
        {
            this->p_rotateLeft(newTempNode->rightChild);
        }
        
        

    }
   
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Gets the node height by traversing the tree
**      Note: https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
**    Function Output: gives the int height value of the tree
**    Side Effects: none
*/

int C_DSW_BST::p_getHeight(S_NODE* root)
{
    if(root == NULL)
    {
        return -1;
    }
    else
    {
        
        int leftHeight = p_getHeight(root->leftChild);
        int rightHeight = p_getHeight(root->rightChild);

        if(leftHeight > rightHeight)
        {
            return(leftHeight + 1);
        }
        if(rightHeight < leftHeight)
        {
            return(rightHeight + 1);
        }
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Deletes the whole tree
**    Function Output: none
**    Side Effects: Removes all the nodes
*/
void C_DSW_BST::p_deleteTree(S_NODE* root)
{
    if(root == NULL)
    {
        return;
    }

    this->p_deleteTree(root->rightChild);
    this->p_deleteTree(root->leftChild);

    delete root;
}

