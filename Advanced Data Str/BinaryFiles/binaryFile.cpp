#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    fstream inputfile;
    fstream outputBinaryFile;
    string inputData;
    char *temp = NULL;

    inputfile.open("inputNormalFile", ios::in);
    outputBinaryFile.open("outputBinaryFile", ios::out|ios::binary);

    if(inputfile.is_open())
    {
        while(!inputfile.eof())
        {
            inputfile >> inputData;
            outputBinaryFile.write(inputData.c_str(), inputData.size());
        }
    }

    inputfile.close();
    outputBinaryFile.close();
}