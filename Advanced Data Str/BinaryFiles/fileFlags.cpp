#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    fstream inputfile;
    fstream outputFile;
    string input;

    inputfile.open("inputNormalFile", ios::in);
    outputFile.open("outputNormalFile", ios::out);

    if(inputfile.is_open())
    {
        while(!inputfile.eof())
        {
            inputfile >> input;
            outputFile << input << "\n";
        }
    }

    inputfile.close();
    outputFile.close();
}