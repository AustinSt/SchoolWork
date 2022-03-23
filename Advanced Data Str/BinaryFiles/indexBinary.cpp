#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;


int main(int argc, char *argv[])
{
    int i = 0;
    int j = 0;
    int swap = 0;
    int myArray[100];
    int indexArray[10]= {0};

    fstream outBinary;
    outBinary.open("sortedBinaryData.dat", ios::in|ios::out|ios::binary);

    for (i = 0; i < 100; ++i)
    {
        myArray[i] = rand() % 1000;
    }

    for(j=0; j< 100; ++j)
    {
        for(i= 0; i< 100; ++i)
        {
            if(myArray[i] > myArray[j])
            {
                swap = myArray[i];
                myArray[i] = myArray[j];
                myArray[j] = swap;
            }
        }
    }
    outBinary.write((char*)myArray, sizeof(int)*100);
    outBinary.seekg(ios::beg);

    swap = 0;
    i = 0;

    do
    {
        if(100 <= myArray[i])
        {
            swap = myArray[i];
        }
        else
        {
            ++i;
        }
    } while (0 == swap);

    
    
    cout << i << " " << swap << endl;

    indexArray[0] = 0;
    indexArray[1] = i;

    /*for (i = 0; i < 100; ++i)
    {
        cout << myArray[i] << endl;
    }*/

    
    

    
    //cout << outBinary.tellg() << endl;
    //cout << outBinary.tellp() << endl;

    //our binary file is in increments of 4

    i = i  * sizeof(int);

    outBinary.seekg(ios::beg+i);
    swap = 0;
    outBinary.read((char*)&swap, sizeof(int));

    cout << swap << endl;

    outBinary.close();

    return 0;
}