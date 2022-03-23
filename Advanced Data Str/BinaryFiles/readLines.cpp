#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
   ifstream inputData;
   int i = 0;
   int temp = 0;

   inputData.open("inNumber");

   /*for(i = 0; i < 9; ++i)
   {
       inputData >> temp;
   }*/
    //try to use our file pointer to retrieve the 10th line from our file.
   inputData.seekg(ios::beg+36);

   inputData >> temp;

   cout << "10th number is: " << temp << endl;

   return 0;
}