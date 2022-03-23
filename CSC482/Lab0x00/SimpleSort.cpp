#include <iostream>
#include <time.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>
#include <fstream>
#include <ctime>

using namespace std;
void swap(int *randomArrayFirst, int *randomArraySecond)
{
    int hold = *randomArrayFirst;
    *randomArrayFirst = *randomArraySecond;
    *randomArraySecond = hold;
}

void bubble(int randomArray[], int sizeArray)
{
    int first,second;

    for(first = 0; first < sizeArray-1; first++)
    {
        for(second = 0; second < sizeArray-first-1; second++)
        {
            if(randomArray[second] > randomArray[second+1])
            {
                swap(&randomArray[second], &randomArray[second+1]);
            }
        }
    }

}

int main()
{
    srand (time(0));

    fstream myFile;

    myFile.open("1000Numbers.txt"); //change .txt for numbers
    int randomArray[1000] = {0}; //change size of array to match numbers.txt
    int dummyArray[1] = {0}; //match size of other array
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    int input = 0;
    int loop = 0;
    double time;
    double dummyTime;
    int base = 0;
    int index = 0;
    int numberofTrials = 0;
    
    
    std::chrono::duration<double> elapsed_seconds;
    std::chrono::duration<double> dummy_elapsed_seconds;
    int sizeArray = sizeof(randomArray) / sizeof(randomArray[0]); //size of array
    int dummysizeArray = sizeof(dummyArray) / sizeof(dummyArray[0]);//size of dummy array
    
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
    
    
   
    do
    {
        
        auto start = std::chrono::system_clock::now(); //time start 
        bubble(dummyArray, dummysizeArray);
        auto end = std::chrono::system_clock::now(); //time end 
        dummy_elapsed_seconds = end-start;
        dummyTime = dummyTime + dummy_elapsed_seconds.count();
       
        loop++;
    } while (numberofTrials > loop);
    
    
    loop = 0;
    do
    {
        shuffle(randomArray, randomArray + sizeArray, std::default_random_engine(seed)); //shuffles the array
        auto start = std::chrono::system_clock::now(); //time start 
        
        bubble(randomArray, sizeArray);
        
        auto end = std::chrono::system_clock::now(); //time end 
        elapsed_seconds = end-start;
        time = time + elapsed_seconds.count();
       
        loop++;
    } while (numberofTrials > loop);
    
    
    
    
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