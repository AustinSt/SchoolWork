#include "unionFind.h"
#include "customErrorClass.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    C_unionFind myClass;

    try
    {
        myClass.initArray(10);
        myClass.initArray(10);
        myClass.printArray();
        myClass.unionNumbers(9,4);
        myClass.unionNumbers(4,2);
        myClass.printArray();
        myClass.isConnected(4,2);
    }
    catch(MyException &e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}