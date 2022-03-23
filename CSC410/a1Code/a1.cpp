#include <iostream>
using namespace std;

int getNum(int L, int H)
{
    int userInput;
    
    cout << "Please enter a number between 4 and 17 inclusive." << endl;
    cin >> userInput;

    if(userInput < L || userInput > H)
    {
        userInput = 0;
        cout << "Wrong value input." << endl;
    }
    
    return userInput;
}

void printArray(int L[], int many)
{
    cout << "List of numbers:" << endl;
    
    for(int x = 0; x < many; x++)
    {
        cout << L[x] << endl;
    }
}

int main()
{
    int numArr[100];
    int holdNum = 0;
    int counter = 0;
    int holdValid = 0;
    int L = 4;
    int H = 17;

    do
    {
        holdNum = getNum(L, H);
        if(holdNum != 0)
        {
            numArr[counter] = holdNum;
            holdValid += holdNum;
            counter++;
        }
        
    } while (holdValid < 50);
    
    cout << "You have entered in: " << counter << " valid numbers" << endl;
    cout << "The sum of these value is: " << holdValid << endl;

    printArray(numArr, counter); 
    
    return 0;
}