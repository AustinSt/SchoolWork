#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main()
{
    const int N=1000;
    int i; 
    float c[1000], d[1000];
    
    
    #pragma acc kernels
    {
        for(i = 0; i<N; i++)
        {
            c[i] = 3.0f*(float)(i+1);
        }
        for(i = 0; i<N; i++)
        {
           d[i] = 2.0f*c[i]; 
        }
    }
}