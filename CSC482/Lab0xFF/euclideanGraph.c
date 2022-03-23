#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main()
{
    int n = 4;
    int maxValue = 100;
    srand(time(0));
    float* x;
    float* y;
    
    float fr;
    x = calloc(n, sizeof(float));
    y = calloc(n, sizeof(float));
    float (*distance)[n] = malloc(sizeof(float[n][n]));

    for(int i = 0; i < n; i++)
    {
        fr = (float)rand()/(float)(RAND_MAX/maxValue);
        x[i] = fr;
        fr = (float)rand()/(float)(RAND_MAX/maxValue);
        y[i] = fr;
        //printf("x: %f   y: %f\n", x[i], y[i]);
    }
    for(int k = 0; k < n; k++)
    {
        for(int z = 0; z < n; z++)
        {
            if(k == z)
            {
                distance[k][z] = 0;
            }
            else
            {
                distance[k][z] = pow((pow(x[k]-x[z],2)+pow(y[k]-y[z],2)),0.5);
            }
            
        }
    }
    for(int g = 0; g < n; g++)
    {
        for(int h = 0; h < n; h++)
        {
            printf("Distance from coord: (%f, %f) to (%f, %f) is: %f\n", x[g], y[g], x[h], y[h], distance[g][h]);
        }
    }
}