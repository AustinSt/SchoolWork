#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

float **generateVertex(int n, int radius, float *x, float *y)//generates random vertex for circular euc graph
{
    
    int* list;//for swap
    float **vertexp = malloc(n*sizeof(float *));//allocates vertex holder for return
    
    list = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)//making 2d array
    {
        vertexp[i] = malloc(2*sizeof(int));
    }
    
    vertexp[0][0] = x[0];//setting 0 vertex to start
    vertexp[0][1] = y[0];

    for(int j = 0; j < n; j++)
    {
        list[j] = j;
        vertexp[j][2] = j;
    }
    size_t a;

    for(a = 1; a < n; a++)//shuffle loop, skips vertex source: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
    {
        size_t p = a + rand() / (RAND_MAX / (n-a)+1);
        int t = list[p];
        list[p] = list[a];
        list[a] = t;
        vertexp[list[a]][0] = x[a];
        vertexp[list[a]][1] = y[a];
        
    }

    return vertexp;//return 2d vertex array
}

float **generateCircEucDistance(int n, float **vertex)//for circular euc distance
{
    float **distancep = malloc(n * sizeof(float *));
    for(int i = 0; i < n; i++)
    {
        distancep[i] = malloc(2*sizeof(float));
    }

    for(int k = 0; k < n; k++)
    {
        for(int z = 0; z < n; z++)
        {
            if(k == z)
            {
                distancep[k][z] = 0;//no distance betweeen itself
            }
            else
            {
                distancep[k][z] = pow((pow(vertex[k][0]-vertex[z][0],2)+pow(vertex[k][1]-vertex[z][1],2)),0.5);
            }
            
        }
    }
    return distancep;
}

float **generateRandomEucDistance(int n, float *x, float *y)//for random euc distance
{
    float **distancep = malloc(n * sizeof(float *));//allocation
    for(int i = 0; i < n; i++)
    {
        distancep[i] = malloc(2*sizeof(float));
    }
    for(int k = 0; k < n; k++)//math
    {
        for(int z = 0; z < n; z++)
        {
            if(k == z)
            {
                distancep[k][z] = 0;
            }
            else
            {
                distancep[k][z] = pow((pow(x[k]-x[z],2)+pow(y[k]-y[z],2)),0.5);
            }
            
        }
    }
    
    return distancep;
}

int **generateRandomCostMatrix(int n, int maxValue)//this is for random cost matrix
{
    int **costMatrixp = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
    {
        costMatrixp[i] = malloc(2*sizeof(int));
    }
    int x = 0;
    for(int i = 0; i < n; i++)
    {
        for(int k = 0; k < n; k++)
        {
            costMatrixp[i][k] = 0;//filling with 0's
        }
    }


    for(int i = 0; i < n; i++)
    {
        for(int k = n-1; k > x; k--)//decrement so it fills the right side of graph
        {
            if(i == k)
            {
                costMatrixp[i][k] = 0;//self edge 0
            }
            else if(rand()%5 == 4 || rand()%10 == 2 || rand()%5 == 0)//for random 0's in the table, so not every vertex is connected
            {
                costMatrixp[i][k] = 0;
                costMatrixp[k][i] = 0;
            }
            else
            {
                costMatrixp[i][k] = rand()%maxValue;
                costMatrixp[k][i] = costMatrixp[i][k];//copy over to the other side
            }
            //printf("i %d  k %d matrix %d\n", i, k, costMatrix[i][k]);
            
        }
        x++;
        
    }
    return costMatrixp;
}

void greedyAlgCircEuc(int n, float **vertex, float **distance)
{
    int count = 1;
    int* visited;
    int* direction;
    float* totalDistance;
    visited = calloc(n, sizeof(int));
    direction = calloc(n, sizeof(int));
    totalDistance = calloc(n, sizeof(float));
    visited[0] = -1;
    direction[0] = -1;
    int index = 0;
    int hold = 0;
    float min = distance[index][1];
    do
    {
        
        
        if(count == 1)
        {
            for(int i = 1; i < n; i++)
            {
                if(distance[hold][i] < min)
                {
                    min = distance[hold][i];
                    index = i;
                    printf("min %.2f\n", min);
                }
            }
        }
        else
        {
            for(int k = 0; k < n; k++)
            {
                if(distance[hold][k] < min && direction[k] == 0)
                {
                    if(distance[hold][k] == 0)
                    {
                        
                    }
                    else
                    {
                        min = distance[hold][k];
                        index = k;
                        printf("k = %d min2 %.2f\n", k, min);
                    }
                    
                }
            }
        }
        
        hold = index;
        totalDistance[count] = min;
        direction[count] = vertex[index][2];
        visited[count] = index;
    
        printf("Count: %d Index: %d   hold: %d  visited: %d\n", count-1, index, hold, visited[count-1]);
        printf("Vertex: %d  Distance: %.2f\n", direction[count], totalDistance[count]);
        min = distance[index][count];
        count++;
       
    } while (count < n);
    
}


int main (int argc, int argv) 
{
    double trialsTime_max = .250; // in seconds
    long long int trialsCount_max = 1, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 7, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;
    srand(time(0));
    float* x;
    float* x2;
    float* y; 
    float* y2;
    float pi = 22.0/7.0;
    float fr;
    
	// If you are printing a results table directly, print your header line here.
	
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=6; n<N_max; n++ ) 
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
        
        int maxValue = 100;
        int radius = 10;
        float stepAngle = (2*pi)/n;
        x = calloc(n, sizeof(float));//for circ euc graph
        y = calloc(n, sizeof(float));//for circ euc graph
        x2 = calloc(n, sizeof(float));//for random euc graph
        y2 = calloc(n, sizeof(float));//for random euc graph
        for(int j = 0; j < n; j++)
        {
            fr = (float)rand()/(float)(RAND_MAX/maxValue);
            x2[j] = fr;
            fr = (float)rand()/(float)(RAND_MAX/maxValue);
            y2[j] = fr;
        }
        for(int k = 0; k < n; k++)
        {
            x[k] = radius * sin(k * stepAngle);
            y[k] = radius * cos(k * stepAngle);
            printf("Vertex: %d  x: %.2f   y: %.2f\n", k, x[k], y[k]);
        }
        printf("\n\n\n");
        int **costMatrix = generateRandomCostMatrix(n, maxValue);
        float **vertex = generateVertex(n, radius, x, y);
        float **circularDistance = generateCircEucDistance(n, vertex);
        float **randomEucDistance = generateRandomEucDistance(n, x2, y2);
        
        /*for(int g = 0; g < n; g++)
        {
            for(int h = 0; h < n; h++)
            {
                if(g == h)
                {
                    continue;
                }
                else
                {
                    printf("Distance from coord: (%f, %f) to (%f, %f) is: %f\n", x2[g], y2[g], x2[h], y2[h], randomEucDistance[g][h]);
                }
            }
        }
        printf("\n\n\n");*/


        for(int i = 0; i < n; i++)
        {
            printf("Vertex: %.0f  x:  %.2f   y:  %.2f\n", vertex[i][2], vertex[i][0], vertex[i][1]);
        }
        printf("\n\n\n");
        for(int g = 0; g < n; g++)
        {
            for(int h = 0; h < n; h++)
            {
                /*if(g == h)
                {
                    continue;
                }*/
                
                
                    printf("Distance from coord: (%.2f, %.2f) to (%.2f, %.2f) is: %.2f\n", vertex[g][0], vertex[g][1], vertex[h][0], vertex[h][1], circularDistance[g][h]);
                
                
            }
        }
        printf("\n\n\n");
        
        
        /*for(int i = 0; i < n; i++)
        {
            //printf("%d  ", i);
            for(int k = 0; k < n; k++)
            {
                printf("%4d", costMatrix[i][k]);
            }
            printf("\n");
            
        }
        printf("\n\n\n");*/
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            greedyAlgCircEuc(n, vertex, circularDistance);
            /******* do any "clean up" after running your algorithm ********/
            free(costMatrix);
            free(vertex);
            free(circularDistance);
            free(randomEucDistance);
            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        trialSetCount = trial; // value of trial when loop ends is how many we did
        trialSetTime = splitTime; // total time for trial set is the last split time
        averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead

        /********* NOW DO A "DUMMY" TRIAL SET TO ESTIMATE THE OVERHEAD TIME ********/
        /* We can just repeat this trialSetCount times, which we know should be faster than above */
        
        splitTime=0.0;
        // get timestamp before set of dummy trials are run:
        trialSetStart = clock();
        for ( trial=0; trial < trialSetCount  && splitTime < trialsTime_max; trial++) 
        {

            /******** any preparations, test input generation, for a single trial run *********/

            /**** DO NOT Call the algorithm function!!! ******/

            /******* do any "clean up" after running your algorithm ********/

            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        dummySetCount = trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount
        dummySetTime = splitTime; // total time for dummy trial set is the last split time
        averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average tiem per dummy trial, including any prep/overhead

        
        estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm
        
        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

    }
}
