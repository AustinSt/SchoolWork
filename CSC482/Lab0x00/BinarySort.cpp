#include <iostream>
#include <time.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>
#include <fstream>
#include <ctime>

using namespace std;

double search(int randomArray[], int base, int sizeArray, int find)
{
    if(base <= sizeArray)
    {
        int middle = (base + sizeArray) / 2;

        if(randomArray[middle] == find)
        {
            return middle;
        }
        if(randomArray[middle] > find)
        {
            return search(randomArray, base, middle-1, find);
        }
        if(randomArray[middle] < find)
        {
            return search(randomArray, middle+1, sizeArray, find);
        }

    }
    
    return -1;

}

int main()
{
    srand (time(0));

    fstream myFile;

    myFile.open("1000Numbers.txt"); //change .txt for numbers
    int randomArray[1000] = {0}; //change size of array to match numbers.txt
    int dummyArray[1] = {0}; //match size of other array
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    int find = 43000; //number to find
    int input = 0;
    int loop = 0;
    double time;
    double dummyTime;
    int base = 0;
    int index = 0;
    int numberofTrials = 0;
    int dummyResult = 0;
    int result = 0;
    std::chrono::duration<double> elapsed_seconds;
    std::chrono::duration<double> dummy_elapsed_seconds;
    int sizeArray = sizeof(randomArray) / sizeof(randomArray[0]); //size of array
    int dummysizeArray = -1;//size of dummy array set at -1 so that it doesn't search for anything
    
    cout << "List number of trials" << endl;
    cin >> numberofTrials;
    
    if(myFile.is_open())
    {
        while(!myFile.eof())
        {
            myFile >> input;
            randomArray[index] = input;
            index++;
        }
    }
    myFile.close();
    
    shuffle(randomArray, randomArray + sizeArray, std::default_random_engine(seed)); //shuffles the array
   
    do//dummy trials
    {
        auto start = std::chrono::system_clock::now(); //time start 
        dummyResult = search(dummyArray, dummysizeArray, find, base);
        auto end = std::chrono::system_clock::now(); //time end 
        dummy_elapsed_seconds = end-start;
        dummyTime = dummyTime + dummy_elapsed_seconds.count();
       
        loop++;
    } while (numberofTrials > loop);
    
    
    loop = 0;
    do//actual trials
    {
        shuffle(randomArray, randomArray + sizeArray, std::default_random_engine(seed)); //shuffles the array
        auto start = std::chrono::system_clock::now(); //time start 
        
        result = search(randomArray, 0, sizeArray-1, find);
        
        auto end = std::chrono::system_clock::now(); //time end 
        elapsed_seconds = end-start;
        time = time + elapsed_seconds.count();
       
        loop++;
    } while (numberofTrials > loop);
    
    
    
    dummyTime = dummyTime/numberofTrials;
    time = time/numberofTrials;
    time = time - dummyTime;
    time = time*1000000;//to show in us time
    
    
    cout << "*********************************************************" << endl;
    cout << "N is equal to: " << sizeArray << endl;
    std::cout << "elapsed overhead time: " << dummyTime*1000000 << "us" <<endl;
    std::cout << "elapsed time: " << time << "us" <<endl;
    cout << "*********************************************************" << endl;
    
    
   
    return 0;
}