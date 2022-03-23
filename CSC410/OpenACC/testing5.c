#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <openacc.h>
#include <math.h>

#define ROWS 10
#define CLMNS 10
int A[ROWS][CLMNS] = {0};
int A_new[ROWS][CLMNS] = {0};

int main()
{
    time_t begin;
    srand(time(0));
    int iterations = 0;
    int max_iterations = 100;
    int i;
    int j;
    
    printf("A matrix\n");
    for(i = 0; i<= ROWS; i++)
    {
        for(j = 0; j<= CLMNS; j++)
        {
            A[i][j] = rand()%100;
            printf("%4d", A[i][j]);
        }
        printf("\n");
    }

    #pragma acc data copy(A), create(A_new)//copies A data before the while loop and copies when out
    while(iterations < max_iterations)
    {
        #pragma acc kernels
        for(i = 1; i< ROWS; i++)
        {
            for(j = 1; j<= CLMNS; j++)
            {
                A_new[i][j] = ceil(0.25*(A[i+1][j]+A[i-1][j]+A[i][j+1]+A[i][j-1]));
            }
        }

        iterations++;
    }
    printf("\n\n");
    printf("A matrix again after math\n");
    for(i = 0; i<= ROWS; i++)
    {
        for(j = 0; j<= CLMNS; j++)
        {
            A[i][j] = rand()%100;
            printf("%4d", A[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    printf("A_NEW matrix again copied again \n");
    for(i = 0; i<= ROWS; i++)
    {
        for(j = 0; j<= CLMNS; j++)
        {
            A_new[i][j] = rand()%100;
            printf("%4d", A[i][j]);
        }
        printf("\n");
    }

    time_t end;
    time(&end);
    

    printf("Program took: %f seconds\n", difftime(end, begin));

    
}