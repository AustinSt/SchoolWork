#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    int wordCount;
    int count;
    string fileName;
    string fromFile;
    ifstream inputFile;

    cout<<argc<<endl; //argc is number count of arguments passed
    for(int i =0; i < argc; ++i)
    {
        cout<<argv[i]<<endl;//argv holds the arguments
    }

    if( 1 >= argc)//asking the user for a file name, spits this out when only 1 argument or less is passed through this 
    {
        cout <<"USAGE:"<<argv[0]<<" <INPUT_FILENAME>"<<endl;

    }
    else
    {
        fileName = argv[1];
        inputFile.open(fileName);

        if(inputFile.is_open())
        {
            inputFile>>wordCount;

            do
            {
                inputFile>>fromFile;
                cout<<fromFile<<endl;
                ++count;
            } while (count<wordCount);

            inputFile.close();
            
        }
        else
        {
            cout<<"Count not open file!"<<endl;
        }
    }
}