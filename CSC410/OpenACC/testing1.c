#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main()
{
    const int N=100;
    float a = 3.0f;
    float x[1000], y[1000];
    for(int i = 0; i < N; ++i)
    {
        x[i] = 2.0f+i;
        y[i] = 1.0f+i;
    }
    
    for(int i = 0; i< N; ++i)
    {
        y[i] = a*x[i] + y[i];
        Sleep(50);
    }
    
    for(int i = 0; i< N; ++i)
    {
        y[i] = a*x[i] + y[i];  
    }
}