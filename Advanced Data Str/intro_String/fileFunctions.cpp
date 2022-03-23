#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void readLine(string fileName)
{
    ifstream inputFile;
    int wordCount;
    int count = 0;
    char fromfile[20];

    inputFile.open(fileName);

    if(inputFile.is_open())
    {
        inputFile>>wordCount;

        do
        {
            inputFile.read(fromfile,20);
            cout<<fromfile<<endl;
            ++count;
        } while (count < wordCount);
        
        inputFile.close();
    }
    else
    {
        cout<<"Could not open file."<<endl;
    }
}

void fromFile(string fileName)
{
    ifstream inputFile;
    string fromfile;
    int wordCount;
    int count = 0;

    inputFile.open(fileName);

    if(inputFile.is_open())
    {
        inputFile >> wordCount;

        do
        {
            inputFile >> fromfile;
            cout<< fromfile << endl;
            ++count;
        } while (count < wordCount);

        inputFile.close();
        
    }
    else
    {
        cout << "Could not open file." << endl;
    }
}

int main(int argc, char *argv[])
{
    string fileName;

    if(1 >= argc)
    {
        cout <<"USAGE:"<<argv[0]<<" <INPUT_FILENAME>"<<endl;
    }
    else
    {
        fileName = argv[1];
        readLine(fileName);
        cout<<"----------------------------------------------"<<endl;
        fromFile(fileName);
    }
    return 0;
}