#include <iostream>
#include <time.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>
#include <fstream>
#include <ctime>

using namespace std;

double search(int randomArray[], int sizeArray, int find, int numberofTrials)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    int loop = 0;
    int result = 0; //dummy value not actually returning a value, just time
    double time = 0;
    std::chrono::duration<double> elapsed_seconds;
    
    do
    {
        shuffle(randomArray, randomArray + sizeArray, std::default_random_engine(seed)); //shuffles the array
        auto start = std::chrono::system_clock::now(); //time start 
        for(int i = 0; i < sizeArray; i++)
        {
            
            if(randomArray[i] == find)
            {
                result = randomArray[i];
                break;
            }
        }
        auto end = std::chrono::system_clock::now(); //time end 
        elapsed_seconds = end-start;
        time = time + elapsed_seconds.count();
        loop++;
    } while (numberofTrials > loop);
    
    return time;

}

int main()
{
    srand (time(0));

    fstream myFile;

    myFile.open("1000Numbers.txt"); //change .txt for numbers
    int randomArray[1000] = {0}; //change size of array to match numbers.txt
    int dummyArray[1] = {0}; //match size of other array
    

    int find = 100; //number to find
    int input = 0;
    
    double time;
    double dummyTime;

    int index = 0;
    int numberofTrials = 0;
    
    int sizeArray = sizeof(randomArray) / sizeof(randomArray[0]); //size of array
    int dummysizeArray = 0;//size of dummy array
    
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
    
    dummyTime = search(dummyArray, dummysizeArray, find, numberofTrials);
    time = search(randomArray, sizeArray, find, numberofTrials);
    dummyTime = dummyTime/numberofTrials;
    time = time/numberofTrials;
    time = time - dummyTime;
    time = time*1000000;
    
    
    cout << "*********************************************************" << endl;
    cout << "N is equal to: " << sizeArray << endl;
    std::cout << "elapsed overhead time: " << dummyTime*1000000 << "us" <<endl;
    std::cout << "elapsed time: " << time << "us" <<endl;
    cout << "*********************************************************" << endl;
    
    
   
    return 0;
}