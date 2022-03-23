#include "RnBTree.h"
#include "customErrorClass.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

using namespace std;

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Constructor for the array size and array
**    Function Output: none
**    Side Effects: none
*/
C_RnBTree::C_RnBTree()
{
    this->p_holdArray = NULL;
    this->p_arraySize = 0;
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Deconstructor for array
**    Function Output: none
**    Side Effects: none
*/
C_RnBTree::~C_RnBTree()
{
    delete[] this->p_holdArray;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for passing the filename
**    Function Output: none
**    Side Effects: none
*/
void C_RnBTree::fromFile(string fileName)
{
    this->p_fromFile(fileName);
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        gets the file name and opens it, puts it into array 
**    Function Output: none
**    Side Effects: fills our private array with the commands
*/
void C_RnBTree::p_fromFile(string fileName)
{
    ifstream inputFile;
    int dummyfromFile;
    int fromFile;
    int count;

    inputFile.open(fileName);

    if(inputFile.is_open())//purely to count for the array size
    {
        while(!inputFile.eof())
        {
            inputFile >> fromFile;
            count++;
        }
    }
    p_arraySize = count;
    inputFile.close();
    
    p_holdArray = new int[p_arraySize];
    count = 0; 

    inputFile.open(fileName);

    if(inputFile.is_open())//actual input of data into array
    {
        while(!inputFile.eof())
        {
            inputFile >> fromFile;
            p_holdArray[count] = fromFile;
            count++;
        }
    }
    inputFile.close();

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for the command section
**    Function Output: none
**    Side Effects: none
*/
void C_RnBTree::assignCommands()
{
    this->p_assignCommands();
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        contains a switch statement that the array puts into a enum
**    Function Output: none
**    Side Effects: each switch statement goes into a different function that does the specified command
*/
void C_RnBTree::p_assignCommands()
{
    int countIndex = 0;
    int indent = 0;
    int holdCommand;
    bool duplicateNum = false;
    bool duplicateDelete = false;
    E_COMMANDS enumVar;

    do
    {
        holdCommand = p_holdArray[countIndex];
        enumVar = E_COMMANDS(holdCommand);

        switch (enumVar)
        {
        case E_COMMANDS::insertNum:
            countIndex++;
            try//check for duplicates
            {
                duplicateNum = this->p_searchTree(root, p_holdArray[countIndex]);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            if(duplicateNum == true)//skips if duplicate
            {
                countIndex ++;
            }
            else
            {
                this->p_insertNum(p_holdArray[countIndex]);
                countIndex++;
            }
            break;
        case E_COMMANDS::deleteNum:
            countIndex++;
            try//check for duplicates
            {
                duplicateDelete = this->p_searchTree(root, p_holdArray[countIndex]);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            if(duplicateDelete == true)
            {
                countIndex++;
            }
            else
            {
                holdNode = this->findNode(root, p_holdArray[countIndex]);
                this->p_deleteNum(holdNode);
                countIndex++;
            }
            
            break;
        case E_COMMANDS::printTree:
            countIndex++;
            this->p_printTree(root, p_indent);
            break;
        case E_COMMANDS::deleteTree:
            countIndex++;
            this->p_deleteTree(root);
            break;
        case E_COMMANDS::exitProgram:
            this->p_exitProgram();
            break;
        default:
        cout << "There was an error with your file please try again." << endl;
        countIndex += 1000000000;
            break;
        }
    } while (countIndex < p_arraySize);
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Creates a new node everytime it is called.
**    Function Output: none
**    Side Effects: calls 2 functions that'll add the new node to the tree and fix color issues
*/
void C_RnBTree::p_insertNum(int number)
{
    if(number <= 0)
    {
        throw MyException("Number inputed is either 0 or below it.");
    }
    else
    {
        S_NODE* node = new S_NODE(number);//node construction
        

        root = insertTree(root, node);//pass the new node into the tree and place it
        
        

        p_fixColor(root, node);//fixes the color and does rotations
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Inserts the numbers into the tree like a normal BST
**    Function Output: returns the root
**    Side Effects: inserts a new node into the tree
*/
S_NODE* C_RnBTree::insertTree(S_NODE* root, S_NODE* node)
{
    
    //a normal BST insertion
    if(root == NULL)
    {
        return node;
    }
    if(node->holdValue < root->holdValue)
    {
        root->leftChild = insertTree(root->leftChild, node);

        root->leftChild->parent = root;
    }
    if(node->holdValue > root->holdValue)
    {
        root->rightChild = insertTree(root->rightChild, node);

        root->rightChild->parent = root;
    }
    return root;
}


/*
**    Author: Austin Stau
**    Function Purpose: 
**        This is the main driver for fixing color issues and calling rotation functions to fix the tree
**    Function Output: none
**    Side Effects: This will change the color and fix color issues considering the rules of the RnB tree
*/
void C_RnBTree::p_fixColor(S_NODE *root, S_NODE *node)
{
    S_NODE *grandParentHold = NULL;
    S_NODE *parentHold = NULL;
    S_NODE *siblingHold = NULL;
    
    
    
   
    while((node != root) && (node->color != 0) && (node->parent->color == 1) && (node->parent != root))
    {
        parentHold = node->parent;
        grandParentHold = node->parent->parent;
        
        
        //if the issue is on the left side of grandparent
        
        if(parentHold == grandParentHold->leftChild)
        {
            
            siblingHold = grandParentHold->rightChild;//hold the sibling
            
            //simple recolor if sibling is red and parent is also red, node is red as well by default
            if(siblingHold != NULL && parentHold->color == 1 && siblingHold->color == 1)
            {
                parentHold->color = 0;
                siblingHold->color = 0;
                grandParentHold->color = 1;
                node = grandParentHold;
            }
            //if sibling is not red, node is right of parent
            if(node == parentHold->rightChild)
            {
                p_leftRotate(root, parentHold);
                node = parentHold;
                parentHold = node->parent;
                if(node->parent->color == 1)
                {
                    node->color = 1;
                    node->parent->leftChild->color = 1;
                    node->parent->color = 0;
                }
                    
            }
            //if sibling is not red, node is left of child
            if(node == parentHold->leftChild)
            {
                
               
                p_rightRotate(root, grandParentHold);
                
                node = grandParentHold;
                
                if(node->parent->color == 1)
                {
                    node->color = 1;
                    node->parent->color = 0;
                    node->parent->leftChild->color = 1;
                }
                
                
            }

        }
        //if issue is right of grandparent
        if(parentHold == grandParentHold->rightChild)
        {
            
            siblingHold = grandParentHold->leftChild;
            //if sibling is red, and parent is red
            if(siblingHold != NULL && parentHold->color == 1 && siblingHold->color == 1)
            {
                
                parentHold->color = 0;
                siblingHold->color = 0;
                grandParentHold->color = 1;
                node = grandParentHold;
            }
            else
            {
                //sibling not red, but node is left of parent
                if(parentHold->leftChild == node)
                {
                    
                    p_rightRotate(root, parentHold);
                    parentHold = node->parent;
                    
                    if(node->color == 1 || node->parent->color == 1)
                    {
                        node->color = 1;
                        node->parent->color = 0;
                        if(node->parent->leftChild != NULL)
                        {
                            node->parent->leftChild->color = 1;
                        }
                        
                    }
                }
                //sibling not red, but node is right of parent
                if(parentHold->rightChild == node)
                {
                   
                    p_leftRotate(root, grandParentHold);
                    node = parentHold;

                    if(node->color == 1 || node->parent->color == 1 || node->parent->rightChild->color == 1)
                    {
                        node->parent->rightChild->color = 1;
                        
                        node->parent->leftChild->color = 1;
                        
                        node->parent->color = 0;
                        
                    }

                }
            }
        }
       
      

    }
   
    //changes root color
    root->color = 0;
    if(root->color == 0 && node->parent == root)//not sure if need
    {
        node->color = 1;
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Rotates the tree to the left "node" can be whatever is passed through.
**    Function Output: none
**    Side Effects: rotates the part of the tree that passed as node
*/
void C_RnBTree::p_leftRotate(S_NODE* root, S_NODE* node)
{
    int holdOgNumber1 = 0;
    S_NODE* holdrightChild;


    
    holdOgNumber1 = node->holdValue;//copy value of newNode
    holdrightChild = node->rightChild;//copy node right of og
    
    //switch values between og child and right child
    node->holdValue = holdrightChild->holdValue;
    node->rightChild->holdValue = holdOgNumber1;
    
    
    node->rightChild = holdrightChild->rightChild;//make the left child of left child the new left child
    
    holdrightChild->rightChild = holdrightChild->leftChild;//make the right child of the left child the new left child
    
    holdrightChild->leftChild = node->leftChild;//because we're swapping here, need to bring the orginial right child back to the original node
    
    node->leftChild = holdrightChild;//makes the hold of the left child the new right child
    
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Rotates right around the "node", the node can be whatever passed through
**    Function Output: none
**    Side Effects: will rotate the tree to the right affecting the whole tree
*/
void C_RnBTree::p_rightRotate(S_NODE* root, S_NODE* node)
{
    
    int holdOgNumber1 = 0;
    S_NODE* holdleftChild;


    
    holdOgNumber1 = node->holdValue;//copy value of newNode
    holdleftChild = node->leftChild;//copy node right of og
    //switch values between og child and right child
    node->holdValue = holdleftChild->holdValue;
    node->leftChild->holdValue = holdOgNumber1;
  
    
    node->leftChild = holdleftChild->leftChild;//make the left child of left child the new left child
   
    holdleftChild->leftChild = holdleftChild->rightChild;//make the right child of the left child the new left child
    
    holdleftChild->rightChild = node->rightChild;//because we're swapping here, need to bring the orginial right child back to the original node
    
    node->rightChild = holdleftChild;//makes the hold of the left child the new right child
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Deletes a number in the tree; takes the held node and runs it through the cases to fix it
**    Function Output: none
**    Side Effects: removes a number from the tree and fixes the tree
*/
void C_RnBTree::p_deleteNum(S_NODE* holdNode)
{
   
    S_NODE *parentNode = NULL;
    S_NODE *siblingNode = NULL;
    S_NODE *secondHold = NULL;
    
    bool checkColor = false;
    
    secondHold = findDeleteNode(holdNode);
    parentNode = holdNode->parent;

    if(parentNode->leftChild == holdNode)//getting sibling node
    {
        siblingNode = parentNode->rightChild;
    }
    if(parentNode->rightChild == holdNode)//same
    {
        siblingNode = parentNode->leftChild;
    }
    if((secondHold == NULL || secondHold->color == 0) && (holdNode->color == 0))//check for color in node we are deleting
    {
        checkColor = true;
    }

    if(secondHold == NULL)
    {
        if(holdNode == root)
        {
            root = NULL;//if the number we are looking for is the root
        }
        else//if not root
        {
            if(checkColor == true)
            {
                this->p_doubleBlack(holdNode);
            }
            else
            {
                if(siblingNode != NULL)
                {
                    siblingNode->color = 1;
                }
            }
        }
        
        if(parentNode->leftChild == holdNode)
        {
                parentNode->leftChild = NULL;
        }
        else
        {
                parentNode->rightChild = NULL;
        }
        delete holdNode;
        
        return;
    }
    if(holdNode->leftChild == NULL || holdNode->rightChild == NULL)
    {
        if(holdNode == root)
        {
            holdNode->holdValue = secondHold->holdValue;
            holdNode->leftChild = NULL;
            holdNode->rightChild = NULL;
            delete secondHold;
        }
        else
        {
            if(parentNode->leftChild == holdNode)
            {
                parentNode->leftChild = NULL;
            }
            else
            {
                parentNode->rightChild = NULL;
            }
            delete holdNode;
        }
        secondHold->parent = parentNode;
        if(checkColor == true)
        {
            this->p_doubleBlack(holdNode);
        }
        else
        {
            secondHold->color = 0;
        }
        return;
    }
    
    p_swap(secondHold, holdNode);
    p_deleteNum(secondHold);
        
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Fixed the double black issue 
**    Function Output: none
**    Side Effects: fix's the color and rotates the tree
*/
void C_RnBTree::p_doubleBlack(S_NODE* node)
{
    
    if(node == root)
    {
        return;
    }
    S_NODE* parentNode = node->parent;
    S_NODE* siblingNode = NULL;
    if(parentNode->leftChild == node)
    {
        siblingNode = parentNode->rightChild;
    }
    else
    {
        siblingNode = parentNode->leftChild;
    }
    if(siblingNode == NULL)
    {
        this->p_doubleBlack(parentNode);
    }
    else
    {
        if(siblingNode->color == 1)
        {
            if(siblingNode = parentNode->rightChild)
            {
                this->p_leftRotate(root, parentNode);
            }
            else
            {
                this->p_rightRotate(root, parentNode);
            }
            
            siblingNode->color = 0;
            parentNode->color = 1;
            this->p_doubleBlack(node);
        }
        else
        {
            if(siblingNode->leftChild->color == 1 || siblingNode->rightChild->color == 1)
            {
                if(siblingNode = parentNode->leftChild)
                {
                    if(siblingNode->leftChild != NULL)
                    {
                        siblingNode->leftChild->color = siblingNode->color;
                        siblingNode->color = parentNode->color;
                        this->p_rightRotate(root, parentNode);
                    }
                    if(siblingNode->rightChild != NULL)
                    {
                        siblingNode->rightChild->color = siblingNode->color;
                        siblingNode->color = parentNode->color;
                        this->p_leftRotate(root, parentNode);
                    }
                }
                if(siblingNode = parentNode->rightChild)
                {
                    if(siblingNode->rightChild != NULL)
                    {
                        siblingNode->rightChild->color = parentNode->color;
                        this->p_leftRotate(root, siblingNode);
                        this->p_rightRotate(root, parentNode);
                    }
                    if(siblingNode->leftChild != NULL)
                    {
                        siblingNode->rightChild->color = siblingNode->color;
                        siblingNode->color = parentNode->color;
                        this->p_leftRotate(root, parentNode);
                    }
                }
            }
    }
        parentNode->color = 0;
    }
    if(siblingNode->leftChild->color == 0 && siblingNode->rightChild->color == 0 && siblingNode != NULL && siblingNode->leftChild != NULL && siblingNode->rightChild != NULL )
    {
        siblingNode->color = 1;
        if(parentNode->color == 0)
        {
            this->p_doubleBlack(node);
        }
        else
        {
            parentNode->color = 0;
        }
    }

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        finds the successor in the tree if one exists
**    Function Output: none
**    Side Effects: the successor will be swapped with node to be deleted
*/

S_NODE* C_RnBTree::findSuccessor(S_NODE* node)
{
    S_NODE *holdNode = node;

    while(holdNode->leftChild != NULL)
    {
        holdNode = holdNode->leftChild;
    }
    return holdNode;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        for the second node to be used to check for color and see if the node is a leaf node or not
**    Function Output: none
**    Side Effects: for deletion of node
*/
S_NODE* C_RnBTree::findDeleteNode(S_NODE* node)
{
    if(node->leftChild == NULL && node->rightChild == NULL)
    {
        return NULL;
    }

    if(node->leftChild != NULL)
    {
        return node->leftChild;
    }
    else
    {
        return node->rightChild;
    }
    
    if(node->leftChild != NULL && node->rightChild != NULL)
    {
        return findSuccessor(node->rightChild);
    }
    

    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        swaps values in the case that the node to be deleted isn't a leaf node
**    Function Output: none
**    Side Effects: eventually after the swap will delete the node in its new place
*/

void C_RnBTree::p_swap(S_NODE* node, S_NODE* successor)
{
    int numTemp = node->holdValue;
    int colorTemp = node->color;

    node->holdValue = successor->holdValue;
    successor->holdValue = numTemp;

    node->color = successor->color;
    successor->color = colorTemp;


}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        To find the node in the tree and make a "copy" of it to delete it later on
**    Function Output: none
**    Side Effects: will eventually delete this node
*/
S_NODE* C_RnBTree::findNode(S_NODE* root, int number)
{
    
    S_NODE *blankNode = root;

    while(blankNode != NULL)
    {
        if(number < blankNode->holdValue)
        {
            if(blankNode == NULL)
            {
                break;
            }
            else
            {
                blankNode = blankNode->leftChild;
            }
        }
        else if(number == blankNode->holdValue)
        {
            break;
        }
        else
        {
            if(blankNode->rightChild == NULL)
            {
                break;
            }
            else 
            {
                blankNode = blankNode->rightChild;
            }
        }
        
    }
    return blankNode;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Prints out the tree 
**    Function Output: Prints the tree to the terminal
**    Side Effects: none
*/
void C_RnBTree::p_printTree(S_NODE* root, int indent)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        try
        {
            
            this->p_printTree(root->leftChild, indent+4);
            if( indent )
            {
                cout<<setw(indent)<< " ";
            }
            cout << root->holdValue;
            if(root->color == 0)//puts the color next to node
            {
                cout << "B" << endl;//B = Black
            }
            if(root->color == 1)
            {
                cout << "R" << endl;//R = Red
            }
            this->p_printTree(root->rightChild, indent+4);
        }
        catch(MyException e)
        {
            cout << e.what()<<endl;
        }
        
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Deletes the current tree 
**    Function Output: none
**    Side Effects: Will delete all the nodes in the current tree, so new tree can be made
*/
void C_RnBTree::p_deleteTree(S_NODE* root)
{
    if(root == NULL)
    {
        throw MyException("Tree is already empty cannot delete");
    }
    else
    {
        //goes down tree and deletes
        //cout << "Deleting current Tree: " << endl;
        this->p_deleteTree(root->rightChild);
        this->p_deleteTree(root->leftChild);

        delete root;
    }
    
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Exits out of the program
**    Function Output: Shows that the program is ending in the terminal
**    Side Effects: Ends program
*/
int C_RnBTree::p_exitProgram()
{
    if(root == NULL)
    {
        cout << "Exiting Program!" << endl;
        exit(0);
    }
    else
    {
        this->p_deleteTree(root);//delete before exiting
        cout << "Exiting Program!" << endl;
        exit(0);
    }
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Searches the tree for duplicates
**    Function Output: Outputs a boolean expression for if a duplicate was found 
**    Side Effects: if it returns true it'll skip over the duplcate
*/
bool C_RnBTree::p_searchTree(S_NODE* root, int number)
{
    if(root == NULL)
    {
        return false;
    }
    if(root->holdValue == number)
    {
        return true;
    }
    else
    {
    
        try
        {
            this->p_searchTree(root->leftChild, number);
            this->p_searchTree(root->rightChild, number);
            if(root->holdValue == number)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
    }
    return false;
}