#ifndef __DSW_BST__H__
#define __DSW_BST__H__

#include <iostream>

using namespace std;

struct S_NODE
{
    int holdValue;
    struct S_NODE *leftChild;
    struct S_NODE *rightChild;
    
};

class C_DSW_BST
{
    public:
        C_DSW_BST();
        ~C_DSW_BST();

        
        void insertValue(S_NODE*& root, S_NODE* newNode);
        void findNode(S_NODE* root, int);
        void printTree(S_NODE*& root, int);
        void sortTree(int, S_NODE* root);
        int getHeight(S_NODE* root);
        void deleteTree(S_NODE* root);

        void createVine(S_NODE* root);
        void rotateRight(S_NODE* newNode);
        void rotateLeft(S_NODE* newNode);
        void createTree();

    private:
        
        int *p_holdArray;
        int p_sizeOfFile;
        int p_calculated;
        
        
        
        void p_insertValue(S_NODE*& root, S_NODE* newNode);
        S_NODE* p_findNode(S_NODE* root, int);
        void p_printTree(S_NODE* root, int);
        void p_sortTree(int, S_NODE* root);
        int p_getHeight(S_NODE* root);
        void p_deleteTree(S_NODE* root);

        void p_createVine(S_NODE* root);
        void p_rotateRight(S_NODE* newNode);
        void p_rotateLeft(S_NODE* newNode);
        void p_createTree();
};

#endif