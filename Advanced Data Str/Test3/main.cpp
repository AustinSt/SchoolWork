#include "customErrorClass.h"
#include <iostream>

using namespace std;

void realTest(int x)
{
    cout << x << endl;
}


void tester(int x)
{
    int a = x;
    
    if(a > 5)
    {
        throw MyException("No");
    }
    else
    {
        try
        {
            realTest(a);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
}



int main(int argc, char *argv[])
{
    int y = 6;
    
    try
    {
        tester(y);
    }
    catch(MyException &e)
    {
        cout << e.what()<<endl;
    }
    
    
    return 0;
}