#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main()
{
    int n = 16;
    int x = 0;
    int maxValue = 50;
    int (*costMatrix)[n] = malloc(sizeof(int[n][n]));
    for(int i = 0; i < n; i++)
    {
        for(int k = 0; k < n; k++)
        {
            costMatrix[i][k] = 0;
        }
    }
    srand(time(0));
    
    for(int i = 0; i < n; i++)
    {
        for(int k = n-1; k > x; k--)
        {
            if(i == k)
            {
                costMatrix[i][k] = 0;
            }
            else if(rand()%5 == 4 || rand()%10 == 2 || rand()%5 == 0)
            {
                costMatrix[i][k] = 0;
                costMatrix[k][i] = 0;
            }
            else
            {
                costMatrix[i][k] = rand()%maxValue;
                costMatrix[k][i] = costMatrix[i][k];
            }
            //printf("i %d  k %d matrix %d\n", i, k, costMatrix[i][k]);
            
        }
        x++;
        
    }
    //printf(" %8d %8d %8d %8d %8d %8d %8d %8d\n", 0,1,2,3,4,5,6,7);
    for(int i = 0; i < n; i++)
    {
        //printf("%d  ", i);
        for(int k = 0; k < n; k++)
        {
            printf("%4d", costMatrix[i][k]);
        }
        printf("\n");
        
    }
}