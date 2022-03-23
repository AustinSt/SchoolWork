#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "customErrorClass.h"

using namespace std;

class C_Numbers{
    public:
        
        C_Numbers();
        ~C_Numbers();
        void readFile(int[100]);
        void printArray();
        void sortArray();

    private:
        int *p_numArray;
        int p_arraySize;
        int p_index;

        
        void p_readFile(int[100]);
        void p_printArray();
        void p_sortArray();
};

/*
**    Author: Alex Wollmann
**    Function Purpose: 
**        Constructor to set default values to the variables
**    Function Output: nothing
**    Side Effects: sets the 3 private variables to 0/null
*/
C_Numbers::C_Numbers(){
    this->p_numArray = NULL;
    this->p_arraySize = 0;
    this->p_index = 0;
}

/*
**    Author: Alex Wollmann
**    Function Purpose: 
**        Deconstructor for numArray
**    Function Output: none
**    Side Effects: deletes the numArray for memory management
*/
C_Numbers::~C_Numbers(){
    delete[] this->p_numArray;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        public function for printing the array
**    Function Output: nothing
**    Side Effects: Exception handling and sents list of numbers to the private function
*/
void C_Numbers::printArray(void){
    MyException excpPrint("Array cannot be printed");
    
    try{
        
        p_printArray();
    }
    catch(const exception& e)
    {
        
        cerr << e.what() << '\n';
    }
    
    
}


/*
**    Author: Austin Stau
**    Function Purpose: 
**        Private function for printing the array
**    Function Output: outputs to screen the array after it has been sorted
**    Side Effects: nothing
*/
void C_Numbers::p_printArray(void){
    if(p_arraySize < 1)
    {
        throw MyException("Array size has changed");
    }
    else
    {
    
        for(int printIndex = 0; printIndex < p_arraySize; printIndex++)
        {
            cout << p_numArray[printIndex] << ", ";
        }
    }
}
    

/*
**    Author: Austin Stau
**    Function Purpose: 
**         Public function for reading the file in
**    Function Output: nothing
**    Side Effects: Exception handling and sends the array to the private function
*/
void C_Numbers::readFile(int fileName[100]){
    
    try{
        p_readFile(fileName);
    }
    catch(const exception& e)
    {
        cout << "Readfile Error" << endl;
        cerr << e.what() << '\n';
    }
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Private function to assign the file array to the private file array for sorting
**    Function Output: none
**    Side Effects: Will set up the private array to be ready to be sorted
*/
void C_Numbers::p_readFile(int fileName[100]){
   
    
    if(fileName[0] == 0)
    {
        throw MyException("First number is NULL, please add a number to the first line of the file");
    }
    else
    {
        p_arraySize = fileName[0];//get array size
        p_numArray = new int[p_arraySize];//assigns size of array dynamically
        
        
        for(int index = 0; index < p_arraySize; index++)
        {
            p_numArray[index] = fileName[index];
        }
    }

    
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Public sort function to be able to access private function
**    Function Output: none
**    Side Effects: Exception handling and starts the private sort array function
*/
void C_Numbers::sortArray()
{
    try
    {
        p_sortArray();
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Bubble sort of the private array.
**    Function Output: nothing
**    Side Effects: Sorts the array and gets it ready to be printed out in the print array function. 
**    Note: Got the bubble sort from https://www.geeksforgeeks.org/bubble-sort/ , modified it a bit to work for my needs
*/
void C_Numbers::p_sortArray()
{
    
    if(p_arraySize < 1)
    {
        throw MyException("Issue with array size please restart cannot sort");
    }
    else
    {
        int firstElement, secondElement, hold;
    
        for(firstElement = 0; firstElement < p_arraySize; firstElement++)
        {
            
            for(secondElement = 0; secondElement < p_arraySize-firstElement; secondElement++)
            {
                if(p_numArray[secondElement] > p_numArray[secondElement+1])
                {
                hold = p_numArray[secondElement];
                p_numArray[secondElement] = p_numArray[secondElement+1];
                p_numArray[secondElement+1] = hold;
                
                }
            }
            
        }
    }
}



/*
**    Author: Austin Stau
**    Function Purpose: 
**        Main function to set the whole environment up
**    Function Output: none
**    Side Effects: Creates constructors and fstream for file read in. Calls functions to sort and print numbers out
*/
int main(int argc, char *argv[]){

    fstream myFile;
    C_Numbers numFile;
    

    int holdArray[100];
    myFile.open("input.dat");
    int iInput = 0;
    int index = 0; 

    if(myFile.is_open())
    {
        while (!myFile.eof())
        {
            myFile >> iInput;
            holdArray[index] = iInput;
            index++;
        }
    }
    numFile.readFile(holdArray);
    myFile.close();
    numFile.sortArray();
    numFile.printArray();

    
    return 0;
}