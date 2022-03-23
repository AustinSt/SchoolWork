#include "DSW_BST.h"
#include "customErrorClass.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    fstream treeFile;
    C_DSW_BST myTree;
    S_NODE* root = NULL;
    S_NODE* newNode = NULL;
    
    int treeHeight = 0;
    int input = 0;
    int indent = 0;
    int num;

    try
    {
        treeFile.open("assign.dat");
        

        if(treeFile.is_open())
        {
            while(!treeFile.eof())
            {
                treeFile >> input;

                newNode = new S_NODE;

                newNode->leftChild = NULL;
                newNode->rightChild = NULL;
                newNode->holdValue = input;
               
                
                myTree.insertValue(root, newNode);
               
                
            }
        }
        treeFile.close();
        
        myTree.printTree(root, indent);
        treeHeight = myTree.getHeight(root);
        myTree.createVine(root);
        indent = 0;
        cout << "-------------------------------------------" << endl;
        myTree.printTree(root, indent);
        myTree.deleteTree(root);
    }
    catch(MyException &e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}