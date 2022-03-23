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
   int temp = 0;
   int inputNum = 0;
   
    
    
   /*inputBinary.open("numberOutBinary", ios::in|ios::binary);

    do
    {
        cout <<"Enter a number below 100: ";
        cin >> inputNum;
    } while (inputNum >= 100);
    

    //inputBinary.seekg(ios::beg+sizeof(int)*inputNum);
    //inputBinary.read((char*)&temp, sizeof(tempStruct));
    

    inputBinary.close();*/

   return 0;
}