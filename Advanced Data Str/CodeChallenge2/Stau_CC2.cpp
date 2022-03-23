#include "RnBTree.h"
#include "customErrorClass.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

using namespace std;

/*
**    Author: Austin Stau
**    Function Purpose: 
**        valdiation of file, only takes 1 file input and it cannot be empty
**    Function Output: bool that the file is good
**    Side Effects: can stop program if bool is false
*/
bool inputValidation(int argc, char *argv[])
{
    bool retValue = false;
    struct stat fileInfo;
    string errorString;
    int error;

    
    if(argc <= 1)
    {
        cout << "No File used." << endl;
        cout << "USAGE: Stau_CodeChallenge2.exe [FILENAME]" <<endl;
        cout << "Exiting..." <<endl; 
        return retValue; 
    }
    if(argc >= 3)
    {
        cout << "Too many files used, only use one." << endl;
        cout << "USAGE: Stau_CodeChallenge2.exe [FILENAME]" <<endl;
        cout << "Exiting..." <<endl;
    }
    else
    {
        error = stat(argv[1], &fileInfo);

        if(0 != error)
        {
            errorString = strerror(errno);
            errorString += ": ";
            errorString += argv[1];
            throw runtime_error(errorString);
        }
        if(0 == fileInfo.st_size)
        {
            errorString = "file is empty: ";
            errorString += argv[1];
            throw runtime_error(errorString);
        }

        retValue = true;

    }
    
    
    return retValue;
}

int main(int argc, char *argv[])
{
    bool retValue = false;
    C_RnBTree newTree;
    string fileName;
    
    
    
    try
    {
        retValue = inputValidation(argc, argv);
        
    }
    catch(runtime_error &e)
    {
        cout<<"RUNTIME_ERROR: " <<e.what()<<endl;
    }
    catch(exception &e)
    {
        cout<<"EXCEPTION: " <<e.what()<<endl;
    }
    

    if(retValue == false)
    {
        return 0;
    }
    
    
        try
        {
            fileName = argv[1];
            newTree.fromFile(fileName);
            newTree.assignCommands();
        }
        catch(MyException &e)
        {
            std::cerr << e.what() << '\n';
        }
    

    
    

    return 0;
    
}