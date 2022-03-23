#include <iostream>
#include "customErrorClass.h"

using namespace std;

double division(int a, int b)
{
    if (b==0)
    {
        throw MyException("myerror");
    }
    else if(b == 1)
    {
        throw logic_error("this error");
    }
    return a/b;
}

int main(int argc, char* argv[])
{
    int x = 50;
    int y = 0;
    double z = 0;
    MyException excp("MyError");

    try
    {
        z = division(x,y);
        cout << z << endl;
    }
    catch(const exception& e)
    {
        cout << "myexception"<< endl;
        cerr << e.what() << '\n';
    }
    catch(const exception& e)
    {
        cout << "exception"<< endl;
        cerr << e.what() << '\n';
    }
    

    return 0;
}