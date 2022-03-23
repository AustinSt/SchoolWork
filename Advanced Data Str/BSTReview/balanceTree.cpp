#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std;

struct S_NODE
{
    int value;
    S_NODE *lNext;
    S_NODE *rNext;
};

class C_bst
{
    public:
        C_bst();
        ~C_bst();
        S_NODE* createNode(int);
        void insert(int);
        void print();
        void sort();
        int height();
    private:
        S_NODE *head;
        int nodeCount;

        void p_CreateTree(int*, int, int);
        S_NODE* p_insert(S_NODE*, S_NODE*);
        void p_inOrderPrint(S_NODE*);
        void p_sort();
        void p_populateArray(S_NODE*, int*, int);
        void recursiveDelete(S_NODE*);
        int p_height(S_NODE*);

};

C_bst::C_bst(void)
{
    this->head = NULL;
    this->nodeCount = 0;
}
C_bst::~C_bst(void)
{
    this->recursiveDelete(this->head);
}

void C_bst::sort()
{
    if(this->nodeCount != 0)
    {
       this->p_sort();
    }
    else
    {
        cout <<"Tree is empty, nothing to balance."<<endl;
    }

}

void C_bst::p_sort()
{
    int *tempArray = new int[this->nodeCount];
    this->p_populateArray(this->head, tempArray, 0);
    this->recursiveDelete(this->head);
    this->head = NULL;
    this->p_CreateTree(tempArray, 0, this->nodeCount-1);

    delete[] tempArray;
}

void C_bst::p_CreateTree(int *myArray, int start, int end)
{
    if(start > end)
    {
        return;
    }
    else
    {
        int middle = floor((start+end)/2);
        this->insert(myArray[middle]);
        this->p_CreateTree(myArray, start, middle-1);
        this->p_CreateTree(myArray, middle+1, end);
    }
}

void C_bst::p_populateArray(S_NODE* node, int *myArray, int index)
{
    if(NULL == node)
    {
        return;
    }
    else
    {
        this->p_populateArray(node->lNext, myArray, index+1);
        myArray[index] = node->value;
        this->p_populateArray(node->rNext, myArray, index +1);
    }
}

void C_bst::recursiveDelete(S_NODE *node)
{
    if(NULL == node)
    {
        return;
    }
    else
    {
        this->recursiveDelete(node->lNext);
        this->recursiveDelete(node->rNext);
        delete node;
    }
}

S_NODE* C_bst::createNode(int value)
{
    S_NODE *temp = new S_NODE;

    temp->value = value;
    temp->lNext = NULL;
    temp->rNext = NULL;

    return temp;
}

void C_bst::insert(int value)
{
    S_NODE *node = this->createNode(value);
    
    if(NULL == this->head)
    {
        this->head = node;
    }
    else
    {
        this->p_insert(this->head, node);
    }

    this->nodeCount++;

    return;
}

void C_bst::print()
{
    if(NULL != this->head)
    {
        this->p_inOrderPrint(this->head);
    }
    else{
        cout <<"Empty Tree"<<endl;
    }
}

int C_bst::height(void)
{
    return this->p_height(this->head);
}

int C_bst::p_height(S_NODE *node)
{
    if (NULL == node)
    {
        return 0;
    }
    else
    {
        int lHeight = 0;
        int rHeight = 0;
        lHeight = this->p_height(node->lNext);
        rHeight = this->p_height(node->rNext);

        if(lHeight > rHeight)
        {
            return lHeight+1;
        }
        else
        {
            return rHeight+1;
        }
    }
}

void C_bst::p_inOrderPrint(S_NODE *node)
{
    if(NULL == node)
    {
        return;
    }
    else
    {
        cout << node->value<<endl;
        this->p_inOrderPrint(node->lNext);
        
        this->p_inOrderPrint(node->rNext);
    }
}

S_NODE* C_bst::p_insert(S_NODE* parent, S_NODE *nodeToInsert)
{
    if(NULL == parent)
    {
        return nodeToInsert;
    }
    else
    {
        if(nodeToInsert ->value < parent->value)
        {
            parent->lNext = this->p_insert(parent->lNext, nodeToInsert);
        }
        else
        {
            parent->rNext = this->p_insert(parent->rNext, nodeToInsert);
        }
    }

    return parent;
}

int main(int argc, char *argv[]){

    C_bst myTree;
    fstream myFile;

    int input;
    int incremenetor = 0;

    myFile.open("treeNumbers.txt");

    if(myFile.is_open())
    {
        while (!myFile.eof())
        {
            myFile >> input;
            myTree.insert(input);
        }
        
    }
    myTree.sort();
    myTree.print();

    

    myFile.close();
    return 0;
}