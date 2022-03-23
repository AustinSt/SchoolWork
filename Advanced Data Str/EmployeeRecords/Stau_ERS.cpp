#include "binaryFile.h"
#include "customErrorClass.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    int choice = 0;
    int fileChoice = 0;
    int sizeChoice = 0;
    C_binaryFile bFile;
    do
    {
        cout << "Please choose a file size (1) Small, (2) Medium, (3) Large." << endl;
        cin >> fileChoice;
        if(cin.fail() || fileChoice < 1 || fileChoice > 3)
        {
            cin.clear();
            cin.ignore();
        }
        if(fileChoice == 1 || fileChoice == 2 || fileChoice == 3)
        {
            sizeChoice = -1;
        }
        else
        {
            cout << "You have chosen the wrong number, please choose (1) , (2), or (3) and hit enter." << endl;
        }
    } while(sizeChoice != -1);
    
    cout << "Sorting binary file, one second" << endl;
    cout << "-------------------------------" << endl;
    try
    {
        bFile.sortBinaryFile(fileChoice);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    cout << "-------------------------------" << endl;
    cout << "The file has been sorted! " << endl;
    
    do
    {
        cout << "Please choose a number to continue." << endl;
        cout << "(1) Retrieve Specific Employee" << endl;
        cout << "(2) Update Employee Record" << endl;
        cout << "(3) Delete Employee's record" << endl;
        cout << "(4) Get a list of Employee's by department and range" << endl;
        cout << "(5) Exit Program" << endl;
        cin >> choice;
        
        switch(choice)
        {
            case 1:
            bFile.getEmployee(fileChoice, 0);
            break;

            case 2:
            bFile.updateEmployee(fileChoice);
            break;

            case 3:
            bFile.deleteEmployee(fileChoice);
            break;

            case 4:
            bFile.findEmployeeRange(fileChoice);
            break;

            case 5:
            choice = 5;
            break;

            default:
            cout << "You have choosen the wrong number\n" << endl;
            break;
        }
    } while (choice != 5);
    
    
}