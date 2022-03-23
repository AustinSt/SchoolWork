#include <iostream>
#include <map>
//#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
     map<int, string> test;//unordered_map<int, string> test
     map<int, string>::iterator myIterator;
     

     test[0] = "potato";//order maps can rearrange these in any order
     test[1] = "tomato";
     test[5] = "banana";
     test.insert(pair<int,string>(8, "strawberry"));

     

     for(myIterator = test.begin(); myIterator != test.end(); ++myIterator)
     {
         cout << myIterator->first<<endl;
         cout << myIterator->second<<endl;
     }
     return 0;
}