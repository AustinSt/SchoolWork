#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NR 7+2
#define NC 9+2
#define GEN 5
#define SEED 13
#define HIGH 17
#define PNUMS 4

pthread_mutex_t lock;
pthread_barrier_t barr;

int checks = 0;
int A[NR][NC] = {0};//first Aay
int B[NR][NC] = {0};//second Aa

void getCount()
{
    pthread_mutex_lock(&lock);
    checks = checks + 1;
    pthread_mutex_unlock(&lock);
}
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
    for(row = 0; row< NR; row++)
    {
        for(column = 0; column<NC; column++)
        {
            printf("%4d", G[row][column]);
        }
        printf("\n");
    }
    
    
}



// given grid, and an particular (x,y) location
//   compute the value of that spot in next generation
int checker(int x, int y)
{
    
    //getCount();
    
    int initial = A[x][y];//incoming number
    int left = A[x][y-1];//left of number
    int right = A[x][y+1];//right of number
    int up = A[x-1][y];//above number in grid
    int down = A[x+1][y];//below number in grid
    int leftUp = A[x-1][y-1];//top left
    int rightUp = A[x-1][y+1];//top right
    int leftDown = A[x+1][y-1];//bottom left
    int rightDown = A[x+1][y+1];//bottom right
    int addAll = initial+left+right+up+down+leftUp+rightUp+leftDown+rightDown;//add all together
    usleep(addAll%11*1500);
    if(addAll%10 == 0)//rules
    {
        return 0;
    }
    if(addAll < 50)
    {
        return initial+3;
    }
    if(addAll > 50 || addAll < 150)
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



void *dowork(void *param)
{
    int i, k;
    long myid;
    myid = (long) param;
    
    for(k = myid; k < NR-1; k = k + PNUMS)
    {
        for(i = 1; i < NC-1; i++)
        {
            B[k][i] = checker(k, i);
            pthread_mutex_lock(&lock);
            checks = checks + 1;
            pthread_mutex_unlock(&lock);
        }
    }
    pthread_barrier_wait(&barr);
    pthread_exit(NULL);
    
}

int main()
{
    int i, j,x,y, count = 0;
    fillGrid( A, SEED , HIGH ); //fills grid
    pthread_t tid[PNUMS];
    pthread_barrier_init(&barr, NULL, PNUMS);
    pthread_mutex_init( &lock, NULL);
    void *status;
    printf("Gen--%d\n", count);
    printGrid(A);
    
    
    do
    {
        for(i = 0; i < PNUMS; i++)
        {
            pthread_create(&tid[i], NULL, dowork, (void *) i+1);
        }
        for(i = 0; i < PNUMS; i++)
        {
            pthread_join(tid[i], NULL);
        }
        count++;
        printf("Gen--%d\n", count);
        printGrid(B);
        for(x =1; x<NR-1; x++)//could have used memcpy
        {
            for(y = 1; y<NC-1; y++)
            {
                A[x][y] = B[x][y];
            }
        }
    } while (count < GEN);
    
    
    
    printf("\n\n");
    printf("Amount of checks: %d\n", checks);
    
    

    return 0;

}

