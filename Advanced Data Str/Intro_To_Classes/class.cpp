#include <iostream>
#include <fstream>
/*
    Goal: create a class that read integers from a file and stores it in an internal array.
*/

using namespace std;

class C_dataArray
{
    public:
        C_dataArray();
        ~C_dataArray();

        void createArray();
        void sortArray();
        //read and write data to array
        //sort the array



    private:
        int p_arraySize;
        int *p_dataArray;

        void p_createArray();
        void p_sortArray();

        //private read and write data to array
        //private sort the array
};

//constructor
C_dataArray::C_dataArray()
{
    this->p_arraySize = 0;
    this->p_dataArray = NULL;
}


//destructor
C_dataArray::~C_dataArray()
{
    delete[] this->p_dataArray;
}


/*
**		Author: Austin Stau
**		Function Purpose:
**          call p_createArray to populate the class variable.
**	    Function Output: None
**      Side Effects: None
*/
void C_dataArray::createArray(void)
{
    //verify that the file exists
    //verify that the file has contents
    //verify that the file contents are numberic vlaues
    //verify that file starts with # of numbers to read in.
    //could do this if feeling ambitious

    this->p_createArray();
}


/*
**		Author: Austin Stau
**		Function Purpose:
**          
To read from input.dat and populate the class variables p_arraySize and p_dataArray
**	    Function Output: None
**      Side Effects: the p_dataArray is populated, the p_arraySize is populated and the input.dat file is read
*/
void C_dataArray::p_createArray(void)
{
    ifstream inputFile;
    int index = 0;

    inputFile.open("input.dat");

    if(inputFile.is_open())
    {
        inputFile >> this->p_arraySize;

        this->p_dataArray = new int[this->p_arraySize];

        for(index = 0; index < this->p_arraySize; ++index)
        {
            inputFile >> this->p_dataArray[index];
        }

    }
    else
    {
        cout << "File couldn't be opened. Exiting...." << endl;
    }

    
}

int main(int argc, char *argv[])
{

    C_dataArray myClass;

    myClass.createArray();

    return 0; 
}