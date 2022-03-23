#ifndef __binaryFile__H__
#define __binaryFile__H__

#include <iostream>

using namespace std;

#pragma pack(1)
struct S_EMPLOYEE
{
    int depart;
    int id;
    char name[30];
};
#pragma pack()
class C_binaryFile
{
    public:
    C_binaryFile();
    ~C_binaryFile();
    int deptCount0 = 0;
    int deptCount1 = 0;
    int deptCount2 = 0;
    int deptCount3 = 0;
    int deptCount4 = 0;
    int secondBinaryLength = 0;
    int locationinFile = 0;
    int holdID = 0;
    int holdDept = 0;
    
    

    void sortBinaryFile(int);
    void getEmployee(int, int);
    void updateEmployee(int);
    void deleteEmployee(int);
    void findEmployeeRange(int);
   
    
    private:
    string p_getEmployee(int, int, int);
    void p_updateEmployee(int, string);
    void p_deleteEmployee(int);
    void p_findEmployeeRange(int, int, int);
    string p_getEmployeeName(int, int, string);
    

};






#endif