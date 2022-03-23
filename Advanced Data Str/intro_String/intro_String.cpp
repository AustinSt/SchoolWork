#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string myString;
    string mySubString;
    char temp;

    myString = "Hello World!";

    cout << myString<<endl;
    
    cout << myString.length()<<endl;
    
    myString.push_back('a');
    cout<<myString<<endl;
    
    myString.pop_back();
    cout<<myString<<endl;

    mySubString = myString.substr(3,myString.length());
    cout<<mySubString<<endl;
    mySubString = myString.substr(3,5);
    cout<<mySubString<<endl;
}