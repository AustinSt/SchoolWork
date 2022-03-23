#include <stdio.h>
#include <pthread.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// establish your sizes using variables or #define
//   so that it is easy to change;
// remainder of code should look at these values
#define NR 5+2
#define NC 4+2
#define GEN 6
#define SEED 4
#define HIGH 6
#define PNUMS 5
pthread_mutex_t lock;
pthread_barrier_t barr;
int checks = 0;
int nr = 1;
int nc = 1;

typedef struct matrix
{
    int a;
    int b;
    int **data;
}matrix;
// fill grid G with random values
// use srand(seed); to set the sequence
// use % high to restrict the range
int getCount()
{
    pthread_mutex_lock(&lock);
    checks++;
    pthread_mutex_unlock(&lock);
}


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
void *checker( void *arr)
{
    matrix arr2 = *((matrix *) arr);
    
    int x = arr2.a;
    int y = arr2.b;
    
    int initial = arr2.data[x][y];//incoming number
    int left = arr2.data[x][y-1];//left of number
    int right = arr2.data[x][y+1];//right of number
    int up = arr2.data[x-1][y];//above number in grid
    int down = arr2.data[x+1][y];//below number in grid
    int leftUp = arr2.data[x-1][y-1];//top left
    int rightUp = arr2.data[x-1][y+1];//top right
    int leftDown = arr2.data[x+1][y-1];//bottom left
    int rightDown = arr2.data[x+1][y+1];//bottom right
    int addAll = initial+left+right+up+down+leftUp+rightUp+leftDown+rightDown;//add all together
    long numRet = -1;
   
    //getCount();
    if(addAll%10 == 0)//rules
    {
        numRet = 0;
    }
    if(addAll < 50)
    {
        numRet = initial+3;
    }
    if(addAll > 50 || addAll < 150)
    {
        initial = initial - 3;
        if(initial <= 0)
        {
            numRet = 0;
        }
        else
        {
            numRet = initial;
        }
    }
    if(initial > 150)
    {
        numRet = 1;
    }
    
    return (void *) numRet;
}


int main()
{
    
    int A[NR][NC] = {0};//first array
    int B[NR][NC] = {0};//second array
    int i =1, j =1,x,y,z, count = 1, holdNum = 0, pcount = 0;
    fillGrid( A, SEED , HIGH ); //fills grid
    pthread_t tids[PNUMS];
    printf("Gen--%d\n", count);
    printGrid(A);
    pthread_barrier_init(&barr, NULL, PNUMS);
    matrix m;
    matrix b;
    b.data = malloc(sizeof(int *) * NR);
    //m.data = malloc(sizeof(int *) * NR);
    void *status;
    m.data = new int*[NC];


    for (i = 0 ; i < NR; i++ )
    {
        
        for (j = 0; j < NC; j++ )
        {
            m.data[i][j] = A[i][j];
        }
    }
    
    printf("Here\n");
    do//loop for generations
    {
        for (i = 1 ; i < NR-1; i++ )
        {
            for (j = 1; j < NC-1; j++ )
            {
                m.a = i;
                m.b = j;
                pthread_create(&tids[pcount], NULL, checker, &m);
                pthread_join(tids[pcount], &status);
                B[i][j] = (long) status;
            }
            pcount++;
        }
        printf("\n\n");
        //pthread_barrier_wait(&barr);
        count++;
        printf("Gen--%d\n", count);
        printGrid(B);
        for(x =0; x<NR; x++)
        {
            for(y = 0; y<NC; y++)
            {
                m.data[x][y] = B[x][y];
            }
        }

    } while (count < GEN);

    for(z = 0; z < PNUMS; z++)
    {
        pthread_join(tids[z], NULL);
    }
    printf("Total checks, %d", checks);
    return 0;

}