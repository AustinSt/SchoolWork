#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct tempStruct
{
    int one;
    int two;
};

int main(int argc, char *argv[])
{
   tempStruct temp;
   fstream inputBinary;
   int i = 0;
   int inputNum = 0;
   

    
   inputBinary.open("numberOutBinary", ios::in|ios::binary);

    do
    {
        cout <<"Enter a number between 0 and 49: ";
        cin >> inputNum;
    } while (inputNum >= 50);
    

    inputBinary.seekg(ios::beg+sizeof(tempStruct)*(inputNum));
    inputBinary.read((char*)&temp, sizeof(tempStruct));
    cout << "Num one: " << temp.one << endl;
    cout << "Num two: " << temp.two << endl;

    //cout << inputBinary.tellg()<<endl;

    

    inputBinary.close();

   return 0;
}