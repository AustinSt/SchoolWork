#ifndef __RnBTree__H__
#define __RnBTree__H__

#include <iostream>

using namespace std;

struct S_NODE
{
    int holdValue;
    int color;
    struct S_NODE *leftChild;
    struct S_NODE *rightChild;
    struct S_NODE *parent;

    S_NODE(int value)
    {
        this->holdValue = value;
        leftChild = NULL;
        rightChild = NULL; 
        parent = NULL;
        this->color = 1;
    }
};

enum class E_COMMANDS //set up for file commands
{
    insertNum = 0,
    deleteNum = 1,
    printTree = 2,
    deleteTree = 8,
    exitProgram = 9
};

class C_RnBTree
{
    public:
       C_RnBTree();
       ~C_RnBTree();
        int count = 0;
       
       void fromFile(string);
       void assignCommands();
       
       

    private:
        int *p_holdArray;
        int p_arraySize;
        int p_indent = 0;
        
        
        void p_fromFile(string);
        void p_assignCommands();
        
        void p_insertNum(int);
        void p_deleteNum(S_NODE*);
        void p_printTree(S_NODE*, int);
        void p_deleteTree(S_NODE*);
        int p_exitProgram();
        bool p_searchTree(S_NODE*, int);
        void p_fixColor(S_NODE*, S_NODE*);
        void p_leftRotate(S_NODE*, S_NODE*);
        void p_rightRotate(S_NODE*, S_NODE*);
        void p_swap(S_NODE*, S_NODE*);
        void p_doubleBlack(S_NODE*);

        S_NODE* findSuccessor(S_NODE*);
        S_NODE* findDeleteNode(S_NODE*);
        S_NODE* findNode(S_NODE*, int);
        S_NODE* insertTree(S_NODE*, S_NODE*);
        S_NODE* root = NULL;
        S_NODE* holdNode = NULL;
        
};

#endif