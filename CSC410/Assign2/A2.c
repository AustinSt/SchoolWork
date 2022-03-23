

#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// establish your sizes using variables or #define
//   so that it is easy to change;
// remainder of code should look at these values
#define NR 5+2
#define NC 5+2
#define GEN 10
#define SEED 2
#define HIGH 20

// fill grid G with random values
// use srand(seed); to set the sequence
// use % high to restrict the range
int fillGrid( int G[][NC], int seed, int high )
{
    srand(seed);
    int hold;
    
    for(int x=1; x<NR-1;x++)//putting random numbers into grid
    {
        for(int z=1; z<NC-1;z++)
        {
           hold = rand()%high;
           G[x][z] = hold;
        }
    }

}

// print out the grid
void printGrid( int G[][NC] )
{
    int row, column = 0;
    for(row = 1; row< NR-1; row++)
    {
        for(column = 1; column<NC-1; column++)
        {
            printf("%4d", G[row][column]);
        }
        printf("\n");
    }
   
    
}

// given grid, and an particular (x,y) location
//   compute the value of that spot in next generation
int checker( int arr[][NC],int x, int y )
{
    int initial = arr[x][y];//incoming number
    int left = arr[x][y-1];//left of number
    int right = arr[x][y+1];//right of number
    int up = arr[x-1][y];//above number in grid
    int down = arr[x+1][y];//below number in grid
    int leftUp = arr[x-1][y-1];//top left
    int rightUp = arr[x-1][y+1];//top right
    int leftDown = arr[x+1][y-1];//bottom left
    int rightDown = arr[x+1][y+1];//bottom right
    int addAll = initial+left+right+up+down+leftUp+rightUp+leftDown+rightDown;//add all together
    //usleep(addAll%11*1500);
    if(addAll%10 == 0)//rules
    {
        return 0;
    }
    if(addAll < 50)
    {
        return initial+3;
    }
    if(addAll > 50 && addAll < 150)
    {
        initial = initial - 3;
        if(initial <= 0)
        {
            return 0;
        }
        else
        {
            return initial;
        }
    }
    if(initial > 150)
    {
        return 1;
    }
}


int main()
{
    
    int A[7][7] = {
    {0,0,0,0,0,0,0},
    {0,11,13,7,5,0,0},
    {0,0,9,6,6,10,0},
    {0,3,8,5,7,10,0},
    {0,7,7,6,10,12,0},
    {0,4,11,9,6,1,0},
    {0,0,0,0,0,0,0}
    };
    int B[NR][NC] = {0};//second array
    int i =1, j =1,x,y, count = 0;
    //fillGrid( A, SEED , HIGH ); //fills grid
    int holdTime = 0;
    int msec = 0;
    printf("A--\n");
    printf("Gen--%d\n", count);
    printGrid(A);
    
    do//loop for generations
    {
        for (i = 1 ; i < NR-1; i++ )
        {
            for (j = 1; j < NC-1; j++ )
            {
                B[i][j] = checker( A, i, j );
            }
        }
        
        printf("\n\n");
        count++;
        printf("Gen--%d\n", count);
        
        printGrid(B);
        for(x =1; x<NR-1; x++)
        {
            for(y = 1; y<NC-1; y++)
            {
                A[x][y] = B[x][y];
            }
        }

    } while (count < GEN);

   
    return 0;

}
