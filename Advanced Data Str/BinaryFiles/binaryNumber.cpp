#include <iostream>
#include <fstream>
#include <string.h>
#include <random>

using namespace std;

struct newStruct
{
    int one;
    int two;
};

int main(int argc, char *argv[])
{
    fstream outBinaryFile , outNormal;
    newStruct tempStruct;
    
    outBinaryFile.open("numberOutBinary", ios::out|ios::binary);
    outNormal.open("inNumber", ios::out);

    srand(time(0));
    int i = 0;
    int j = 0;

    for( i = 0; i<100; ++i)
    {
        j = rand()%1000+1;
        outNormal << j << "\n";
        outBinaryFile.write((char*)&j, sizeof(int));
    }

    outBinaryFile.close();
    outNormal.close();
    outBinaryFile.open("numberOutBinary", ios::in|ios::binary);
    
    cout <<"Reading in now" << endl;

    for(i = 0; i < 100; i+=2)
    {
        //outBinaryFile.read((char*)&j, sizeof(int));
        outBinaryFile.read((char*)&tempStruct, sizeof(tempStruct));
        cout << tempStruct.one << "|" << tempStruct.two <<endl;
    }
    return 0;
}