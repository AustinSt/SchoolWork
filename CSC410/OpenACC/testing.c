#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

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
    
    #pragma acc kernels//more implicit, compiler finds parallelism, compiler deems what is safe
    for(int i = 0; i< N; ++i)
    {
        y[i] = a*x[i] + y[i];
    }
    
    #pragma acc parallel loop //more explicit, OpenMP parallels, must ensure safe parallelism
    for(int i = 0; i< N; ++i)
    {
        y[i] = a*x[i] + y[i];
    }
    
}