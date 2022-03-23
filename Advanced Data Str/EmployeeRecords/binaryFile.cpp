#include "binaryFile.h"
#include "customErrorClass.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Not used
**    Function Output: none
**    Side Effects: none
*/
C_binaryFile::C_binaryFile()
{

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Not used
**    Function Output: none
**    Side Effects: none
*/
C_binaryFile::~C_binaryFile()
{

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**       Sorts based on which file the user asked for
**    Function Output: none
**    Side Effects: creates a new file that is sorted by department id
*/
void C_binaryFile::sortBinaryFile(int fileChoice)
{
    S_EMPLOYEE EmployeeRec;
    fstream binaryFile;
    fstream sorted_BinaryFile;
    int firstLoop = 0, secondLoop = 0, thirdLoop = 0, fourthLoop = 0, fifthLoop = 0;
    int binaryLength = 0;
    

    if(fileChoice == 1)//small sort
    {
        binaryFile.open("smallBinaryInput.dat", ios::in|ios::binary);
        sorted_BinaryFile.open("Sorted_smallBinaryInput.dat", fstream::out|fstream::binary);
        
        binaryFile.seekg(0, binaryFile.end);
        binaryLength = binaryFile.tellg();
        binaryFile.seekg(0, binaryFile.beg);
        cout << "Sorting..." << endl;

        for(firstLoop = 0; firstLoop < binaryLength; firstLoop+=38)//loops through and reads the first department and places it at the front of the file
        {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 0)
            {
                deptCount0 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
        }
        sorted_BinaryFile.close();
        sorted_BinaryFile.open("Sorted_smallBinaryInput.dat", ios::app);//use of the append function
    }
    if(fileChoice == 2)//medium sort
    {
        binaryFile.open("mediumBinaryInput.dat", ios::in|ios::binary);
        sorted_BinaryFile.open("Sorted_mediumBinaryInput.dat", fstream::out|fstream::binary);
        
        binaryFile.seekg(0, binaryFile.end);
        binaryLength = binaryFile.tellg();
        binaryFile.seekg(0, binaryFile.beg);
        cout << "Sorting...." << endl;

        for(firstLoop = 0; firstLoop < binaryLength; firstLoop+=38)
        {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 0)
            {
                deptCount0 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
        }
        sorted_BinaryFile.close();
        sorted_BinaryFile.open("Sorted_mediumBinaryInput.dat", ios::app);//use of the append function
    }
    if(fileChoice == 3)//for large sort
    {
        binaryFile.open("largeBinaryInput.dat", ios::in|ios::binary);
        sorted_BinaryFile.open("Sorted_largeBinaryInput.dat", fstream::out|fstream::binary);
        
        binaryFile.seekg(0, binaryFile.end);
        binaryLength = binaryFile.tellg();
        binaryFile.seekg(0, binaryFile.beg);
        cout << "Sorting..." << endl;

        for(firstLoop = 0; firstLoop < binaryLength; firstLoop+=38)
        {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 0)
            {
                deptCount0 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
        }
        sorted_BinaryFile.close();
        sorted_BinaryFile.open("Sorted_largeBinaryInput.dat", ios::app);//use of the append function
    }
    //standard sort for all files
    binaryFile.seekg(0, binaryFile.beg);
    for(secondLoop = 0; secondLoop < binaryLength; secondLoop+=38)
    {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 1)//for first dept and onwards same iteration with different depts
            {
                deptCount1 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
    }
    binaryFile.seekg(0, binaryFile.beg);
    for(thirdLoop = 0; thirdLoop < binaryLength; thirdLoop+=38)
    {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 2)
            {
                deptCount2 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
    }
    binaryFile.seekg(0, binaryFile.beg);
    for(fourthLoop = 0; fourthLoop < binaryLength; fourthLoop+=38)
    {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 3)
            {
                deptCount3 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
    }
    binaryFile.seekg(0, binaryFile.beg);
    for(fifthLoop = 0; fifthLoop < binaryLength; fifthLoop+=38)
    {
            binaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

            if(EmployeeRec.depart == 4)
            {
                deptCount4 += 38;
                sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));
            }
    }
    //end
    //start of checking if the file sorting was correct -- should be same size
    sorted_BinaryFile.seekg(0, sorted_BinaryFile.end);
    secondBinaryLength = sorted_BinaryFile.tellg();
    sorted_BinaryFile.seekg(0, sorted_BinaryFile.beg);
    

    binaryFile.close();
    sorted_BinaryFile.close();

    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Public function for the get specific employee by id number and dept
**    Function Output: Will show the user if it exists, if not will display not found
**    Side Effects: none
*/
void C_binaryFile::getEmployee(int fileChoice, int EmployChoice)
{
    string employeeInfo;
    string repeatChoice;
    
    string userName;
    int range = 0;
    string choiceForSeach;
    int id = 0;
    int userSearchChoice = 0;
    bool confirmSecond = false;
    bool confirmFirst = false;
    bool confirmThird = false;
    
    do
    {
        do
        {
            
            
            do//employee id ask
            {
                cout << "Please give me an employee's id number." << endl;
                cin >> id;
                if(cin.fail() || id < 0 || id > 999999)//checks to make sure the user doesn't give bad input
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid entry, please try again." << endl;
                }
                else
                {
                    confirmThird = true;
                }
            } while (confirmThird == false);
            
            
            //department ask
            cout << "Please give me an employee's department number:\n (0)Accounting\n (1)Business\n (2)Human Resources\n (3)Sales\n (4)Production " << endl;
            cin >> range;
            if(cin.fail())//bad input
            {
                cin.clear();
                cin.ignore();
                cout << "You have choosen a wrong number." << endl;
            }
            else if(range == 0 || range == 1 || range == 2 || range == 3 || range == 4)
            {
                
                employeeInfo = this->p_getEmployee(fileChoice, range, id);
                confirmFirst = true;
            }
            else
            {
                cout << "You have chosen a wrong number, please try again." << endl;
            }
            
        } while (confirmFirst == false);
        holdID = id;//for later data handling
        holdDept = range; //for later data handling
        cout << "Thank you, finding employee now." << endl;
        cout << "--------------------------------" << endl;
        
        if(employeeInfo == "0")
        {
            cout << "No person with this dept number and id exist, try again" << endl;
            cout << "Do you wish to continue Y|N?" << endl;
            cin >> repeatChoice;
            if(repeatChoice == "N" || repeatChoice == "n")
            {
                confirmSecond = true;
            }
        }
        else
        {
            cout << "Here is the full information on the employee: " << employeeInfo << endl; 
            if(EmployChoice == 0)
            {
                cout << "Do you wish to continue Y|N?" << endl;
                cin >> repeatChoice;
                if(repeatChoice == "N" || repeatChoice == "n")
                {
                    confirmSecond = true;
                }
            }
            if(EmployChoice == 1)
            {
                confirmSecond = true;
            }
        }
            
    } while (confirmSecond == false);
    

    
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**       Private function that goes into the sorted file and finds the id number that matches
**    Function Output: returns a string with employee's info and sets a pointer in the file to the location of that found employee.
**    Side Effects: none
*/
string C_binaryFile::p_getEmployee(int fileChoice, int range, int id)
{
    fstream sorted_BinaryFile;
    int holdID = 0;
    int holdDept = 0;
    string wholeInfo = "0";
    string holdName = "0";
    S_EMPLOYEE EmployeeRec;
    int index = 0;
    int holdRange = 0;
    int length = 0;

    locationinFile = 0;
    
    if(fileChoice == 1)//filechoice
    {
        sorted_BinaryFile.open("Sorted_smallBinaryInput.dat", ios::in|ios::binary);
    }
    if(fileChoice == 2)
    {
        sorted_BinaryFile.open("Sorted_mediumBinaryInput.dat", ios::in|ios::binary);
    }
    if(fileChoice == 3)
    {
        sorted_BinaryFile.open("Sorted_largeBinaryInput.dat", ios::in|ios::binary);
    }
    sorted_BinaryFile.seekg(ios::beg);
    if(range == 0)//binary file index
    {
        holdRange = 0;
        length = deptCount0;
        
        sorted_BinaryFile.seekg(0, sorted_BinaryFile.beg);
       
    }
    if(range == 1)
    {
        holdRange = deptCount0;
        length = deptCount0+deptCount1;
        
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    if(range == 2)
    {
        holdRange = deptCount0+deptCount1;
        length = deptCount0+deptCount1+deptCount2;
        
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    if(range == 3)
    {
        holdRange = deptCount0+deptCount1+deptCount2;
        length = deptCount0+deptCount1+deptCount2+deptCount3;
       
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    if(range == 4)
    {
        
        holdRange = deptCount0+deptCount1+deptCount2+deptCount3;
        length = deptCount0+deptCount1+deptCount2+deptCount3+deptCount4;
        
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    

    for(index = holdRange; index < length; index+=38)//loop through specified index
    {
        sorted_BinaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));
        
        if(id == EmployeeRec.id)//stops loop if id is found
        {
            locationinFile = sorted_BinaryFile.tellg();
            break;
        }
    }
    
    if(id == EmployeeRec.id)//if found it passes the info, if not it sends back '0'
    {
        holdDept = EmployeeRec.depart;
        holdID = EmployeeRec.id;
        holdName = EmployeeRec.name;
        

        
        wholeInfo = to_string(holdDept) + " | "  + to_string(holdID) + " | " + holdName;
    }
  
    
    
    sorted_BinaryFile.close();

    return wholeInfo;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Public function for changing the employee's name
**    Function Output: ask user for new name
**    Side Effects: goes to private function
*/
void C_binaryFile::updateEmployee(int fileChoice)
{
    
   
    char name[30];
    string holdName;
    int holdSLength;
    bool check = false;

    this->getEmployee(fileChoice, 1);//get employee info, hold pointer location in global variable
    do
    {
        cout << "Please enter a name you wish to change this entry to, 30 characters max" << endl;
        cin >> holdName;//new name
        if(cin.fail())//check for bad input
        {
            cin.clear();
            cin.ignore();
            cout << "Bad input, exiting" << endl;
        }
        holdSLength = holdName.length();
        if(holdSLength > 30 || holdSLength == 0)//name check
        {
            cout << "Too large of a name or too small, please try again." << endl;
        }
        else
        {
            check = true;
        }
    } while (check == false);
    
    this->p_updateEmployee(fileChoice, holdName);//goes to private function
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        private function for changing name, goes to pointer set by getemployee function
**    Function Output: prints to screen the new name with id and dept #
**    Side Effects: changes name in sorted binary file to whatever the user inputed
*/
void C_binaryFile::p_updateEmployee(int fileChoice, string holdName)
{
    
    S_EMPLOYEE EmployeeRec;
    fstream sorted_BinaryFile;
    char name[30];
    string printOut;
    
    
    strcpy(name, holdName.c_str());//copy the user input into a char array
    
    if(fileChoice == 1)//filechoice
    {
        sorted_BinaryFile.open("Sorted_smallBinaryInput.dat", fstream::in|fstream::out|fstream::binary);
    }
    if(fileChoice == 2)
    {
        sorted_BinaryFile.open("Sorted_mediumBinaryInput.dat", ios::in|ios::out|ios::binary);
    }
    if(fileChoice == 3)
    {
        sorted_BinaryFile.open("Sorted_largeBinaryInput.dat", ios::in|ios::out|ios::binary);
    }
    
    sorted_BinaryFile.seekg(ios::beg+locationinFile-38);//location file was stored when previously looked up
    sorted_BinaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));//read based off of pointer location

    holdDept = EmployeeRec.depart;//just in case
    holdID = EmployeeRec.id;

    strncpy(EmployeeRec.name, name, 30);//copies the user input into the struct to be written into file

    sorted_BinaryFile.seekg(ios::beg+locationinFile-38);//need to go back to point location
    sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));//writes

    sorted_BinaryFile.close();

    printOut = this->p_getEmployee(fileChoice, holdDept, holdID);//prints out new info
    cout << "Here is your new entry: " << endl;
    cout << printOut << endl;
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Public function, 
**    Function Output: prints to screen, making sure that user wants to delete
**    Side Effects: goes to private function
*/
void C_binaryFile::deleteEmployee(int fileChoice)
{
    string holdChoice;
    bool check = false;

    this->getEmployee(fileChoice, 1);//get employee info
    do
    {
        cout << "Are you sure you wish to delete this entry this is final Y|N?" <<endl;
        cin >> holdChoice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Bad input, exiting." << endl;
        }
        if(holdChoice == "Y" || holdChoice == "y")
        {
            this->p_deleteEmployee(fileChoice);
            check = true;
        }
        else
        {
            check = true;
        }
    } while (check == false);
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        private function for deleting employee the whole 38 bytes, set id and dept to -1 and fills name with "0"
**    Function Output: prints to screen that entry was deleted
**    Side Effects: deletes the while 38 bytes for 1 entry
*/
void C_binaryFile::p_deleteEmployee(int fileChoice)
{
    S_EMPLOYEE EmployeeRec;
    fstream sorted_BinaryFile;
    string printOut;
    
    
    if(fileChoice == 1)//filechoice
    {
        sorted_BinaryFile.open("Sorted_smallBinaryInput.dat", fstream::in|fstream::out|fstream::binary);
    }
    if(fileChoice == 2)
    {
        sorted_BinaryFile.open("Sorted_mediumBinaryInput.dat", ios::in|ios::out|ios::binary);
    }
    if(fileChoice == 3)
    {
        sorted_BinaryFile.open("Sorted_largeBinaryInput.dat", ios::in|ios::out|ios::binary);
    }

    sorted_BinaryFile.seekg(ios::beg+locationinFile-38);//goes to pointer
    sorted_BinaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));//reads info

    EmployeeRec.depart = -1;//setting to deletion
    EmployeeRec.id = -1;
    for(int index = 0; index < 30; index++)//fill char name with 0's
    {
        EmployeeRec.name[index] = '\0';
    }
    

    sorted_BinaryFile.seekg(ios::beg+locationinFile-38);//go back to pointer
    sorted_BinaryFile.write((char*)&EmployeeRec, sizeof(EmployeeRec));//write

    
    cout << "Your requested entry has been deleted." << endl;
    

    sorted_BinaryFile.close();
}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        Public function for finding the range of employees. This function sets up the index by dept #
**    Function Output: prints to screen choices for the user to scearch based on the current entries in the file
**    Side Effects: goes to private function
*/
void C_binaryFile::findEmployeeRange(int fileChoice)
{
    int deptChoice = -1;
    
    int topRange = 0;
    bool firstChoice = false;
    bool secondChoice = false;
    string keepGoing;

    do
    {
        cout << "Please select which department you wish to see\n (0)Accounting\n (1)Business\n (2)Human Resources\n (3)Sales\n (4)Production " << endl;
        cin >> deptChoice;
        if(deptChoice == 0 || deptChoice == 1 || deptChoice == 2 || deptChoice == 3 || deptChoice == 4)//index choice
        {
                if(deptChoice == 0)//index
                {
                    do
                    {
                        cout << "Here is the current total entries for the Accounting department: " << deptCount0/38 << endl;
                        cout << "Please choose the max amount of entries you would like to see, cannot go below two or above the max entries" << endl;
                        cin >> topRange;
                        if(topRange < 2 || topRange > deptCount0/38)
                        {
                            cout << "Sorry you picked an invalid range of entries, try again." << endl;
                        }
                        else
                        {
                            this->p_findEmployeeRange(fileChoice, topRange, deptChoice);
                            secondChoice = true;
                        }
                        
                    } while (secondChoice == false);
                }
                if(deptChoice == 1)
                {
                    do
                    {
                        cout << "Here is the current total entries for the Business department: " << deptCount1/38 << endl;
                        cout << "Please choose the max amount of entries you would like to see, cannot go below two or above the max entries" << endl;
                        cin >> topRange;
                        if(topRange < 2 || topRange > deptCount1/38)
                        {
                            cout << "Sorry you picked an invalid range of entries, try again." << endl;
                        }
                        else
                        {
                            
                            this->p_findEmployeeRange(fileChoice, topRange, deptChoice);
                            secondChoice = true;
                        }
                        
                    } while (secondChoice == false);
                }
                if(deptChoice == 2)
                {
                    do
                    {
                        cout << "Here is the current total entries for the Human Resources department: " << deptCount2/38 << endl;
                        cout << "Please choose the max amount of entries you would like to see, cannot go below two or above the max entries" << endl;
                        cin >> topRange;
                        if(topRange < 2 || topRange > deptCount2/38)
                        {
                            cout << "Sorry you picked an invalid range of entries, try again." << endl;
                        }
                        else
                        {
                            this->p_findEmployeeRange(fileChoice, topRange, deptChoice);
                            secondChoice = true;
                        }
                        
                    } while (secondChoice == false);
                }
                if(deptChoice == 3)
                {
                    do
                    {
                        cout << "Here is the current total entries for the Sales department: " << deptCount3/38 << endl;
                        cout << "Please choose the max amount of entries you would like to see, cannot go below two or above the max entries" << endl;
                        cin >> topRange;
                        if(topRange < 2 || topRange > deptCount3/38)
                        {
                            cout << "Sorry you picked an invalid range of entries, try again." << endl;
                        }
                        else
                        {
                            this->p_findEmployeeRange(fileChoice, topRange, deptChoice);
                            secondChoice = true;
                        }
                        
                    } while (secondChoice == false);
                }
                if(deptChoice == 4)
                {
                    do
                    {
                        cout << "Here is the current total entries for the Production department: " << deptCount4/38 << endl;
                        cout << "Please choose the max amount of entries you would like to see, cannot go below two or above the max entries" << endl;
                        cin >> topRange;
                        if(topRange < 2 || topRange > deptCount4/38)
                        {
                            cout << "Sorry you picked an invalid range of entries, try again." << endl;
                        }
                        else
                        {
                            this->p_findEmployeeRange(fileChoice, topRange, deptChoice);
                            secondChoice = true;
                        }
                        
                    } while (secondChoice == false);
                }
                cout << "Do you wish to find some more entries Y | N?" << endl;//repeat?
                cin >> keepGoing;
                if(keepGoing == "Y" || keepGoing == "y")
                {
                    continue;
                }
                else
                {
                    firstChoice = true;
                }
                
        }
        else
        {
                cout << "You have chosen a wrong number, please try again." << endl;
        }
        
    } while (firstChoice == false);
    

}

/*
**    Author: Austin Stau
**    Function Purpose: 
**        private function for finding employee range, will find based on the amount of entries the user specified.
**    Function Output: prints to screen the entries the user wanted
**    Side Effects: none
*/
void C_binaryFile::p_findEmployeeRange(int fileChoice, int topRange, int deptChoice)
{
    fstream sorted_BinaryFile;
    S_EMPLOYEE EmployeeRec;
    int range = deptChoice;
    int holdRange = 0;
    int length = 0;
    
    if(fileChoice == 1)//filechoice
    {
        sorted_BinaryFile.open("Sorted_smallBinaryInput.dat", ios::in|ios::binary);
    }
    if(fileChoice == 2)
    {
        sorted_BinaryFile.open("Sorted_mediumBinaryInput.dat", ios::in|ios::binary);
    }
    if(fileChoice == 3)
    {
        sorted_BinaryFile.open("Sorted_largeBinaryInput.dat", ios::in|ios::binary);
    }

    if(range == 0)//index
    {
        holdRange = 0;
        length = deptCount0;
        
        sorted_BinaryFile.seekg(0, sorted_BinaryFile.beg);
       
    }
    if(range == 1)
    {
        holdRange = deptCount0;
        length = deptCount0+deptCount1;
        
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    if(range == 2)
    {
        holdRange = deptCount0+deptCount1;
        length = deptCount0+deptCount1+deptCount2;
        
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    if(range == 3)
    {
        holdRange = deptCount0+deptCount1+deptCount2;
        length = deptCount0+deptCount1+deptCount2+deptCount3;
       
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    if(range == 4)
    {
        
        holdRange = deptCount0+deptCount1+deptCount2+deptCount3;
        length = deptCount0+deptCount1+deptCount2+deptCount3+deptCount4;
        
        sorted_BinaryFile.seekg(ios::beg+holdRange);
        
    }
    cout << "Getting your info now...." << endl;
    topRange += holdRange;//adding the range the user specified
    
    for(int index = holdRange; index < topRange; index++)
    {
        sorted_BinaryFile.read((char*)&EmployeeRec, sizeof(EmployeeRec));

        cout << "Dept: " << EmployeeRec.depart << " | ID: " << EmployeeRec.id << " | Name: " << EmployeeRec.name << endl;
    }

    sorted_BinaryFile.close();
}