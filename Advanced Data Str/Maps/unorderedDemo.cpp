#include <iostream>

#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
     unordered_map<int, string> test;
     unordered_map<int, string>::iterator myIterator;
     

     test[0] = "potato";
     test[5] = "banana";
     test[1] = "tomato";
     
     test.insert(pair<int,string>(8, "strawberry"));
     test.insert(pair<int,string>(9, "strawberry"));
     

     for(myIterator = test.begin(); myIterator != test.end(); ++myIterator)
     {
         cout << myIterator->first<<endl;
         cout << myIterator->second<<endl;
     }

    myIterator = test.find(10);

    if(myIterator!=test.end())
    {
        cout << "myIterator->first = "<<myIterator->first<<endl;
        cout << "myIterator->second = "<<myIterator->second<<endl;
    }
    else
    {
        cout << "Key does not exist" <<endl;
    }

     return 0;
}