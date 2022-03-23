#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>


float cost = 0;
float **generateVertex(int n, int radius, float *x, float *y)//generates random vertex for circular euc graph
{
    
    int* list;//for swap
    /*float **vertexp = malloc(n*sizeof(float *));//allocates vertex holder for return
    for(int i = 0; i < n; i++)//making 2d array
    {
        vertexp[i] = malloc(2*sizeof(int));
    }*/
    list = calloc(n, sizeof(int));
    
    float **vertexp; 
    vertexp = malloc(n * sizeof(*vertexp));
    for(int i = 0; i < n; i++)
    {
        vertexp[i] = malloc(n*sizeof(vertexp[0]));
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
    float **distancep; 
    distancep = malloc(n * sizeof(*distancep));
    for(int i = 0; i < n; i++)
    {
        distancep[i] = malloc(n*sizeof(distancep[0]));
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
    float **distancepp; 
    distancepp = malloc(n * sizeof(*distancepp));
    for(int i = 0; i < n; i++)
    {
        distancepp[i] = malloc(n*sizeof(distancepp[0]));
    }
    for(int k = 0; k < n; k++)//math
    {
        for(int z = 0; z < n; z++)
        {
            if(k == z)
            {
                distancepp[k][z] = -1;
            }
            else
            {
                distancepp[k][z] = pow((pow(x[k]-x[z],2)+pow(y[k]-y[z],2)),0.5);
            }
            
        }
    }
    
    return distancepp;
}

float **generateRandomCostMatrix(int n, int maxValue)//this is for random cost matrix
{
    float **costMatrixp; 
    costMatrixp = malloc(n * sizeof(*costMatrixp));
    for(int i = 0; i < n; i++)
    {
        costMatrixp[i] = malloc(n*sizeof(costMatrixp[0]));
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
            /*else if(rand()%5 == 4 || rand()%10 == 2 || rand()%5 == 0)//for random 0's in the table, so not every vertex is connected
            {
                costMatrixp[i][k] = 0;
                costMatrixp[k][i] = 0;
            }*/
            else
            {
                costMatrixp[i][k] = (float)rand()/(float)(RAND_MAX/maxValue);
                costMatrixp[k][i] = costMatrixp[i][k];//copy over to the other side
            }
            //printf("i %d  k %d matrix %d\n", i, k, costMatrix[i][k]);
            
        }
        x++;
        
    }
    return costMatrixp;
}
void greedyAlg(int n, float **vertex, float **distance)//code from https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/ modified from c++ / c# to c
{
   
    float sum = 0;
    int counter = 0;
    int j = 0, i = 0;
    float min = INT_MAX;
    int* visited;
    int* holdRoute;
    holdRoute = calloc(n, sizeof(int));
    visited = calloc(n, sizeof(int));
    visited[0] = 1;
    int* route;
    route = calloc(n, sizeof(int));
    
    while(i < n && j < n)
    {
        
        if(counter >= n-1)
        {
            break;
        }
        if(j != i && (visited[j] == 0))
        {
            if(distance[i][j] < min)
            {
                min = distance[i][j];
                route[counter] = j + 1;
            }
        }
   
        j++;
       
        if(j == n)
        {
            
            sum = sum + min;
            min = INT_MAX;
            visited[route[counter]-1] = 1;
            j = 0;
            i = route[counter] - 1;
            holdRoute[counter] = vertex[i][2];
            counter++;
        }
    }
   
    i = route[counter-1] - 1;
    
    for(j = 0; j < n; j++)
    {
        
        if((i != j) && distance[i][j] < min)
        {
            min = distance[i][j];
            route[counter] = j + 1;
        }
    }
    sum = sum + min;
    
    printf("Route: 0, ");
    for(int l = 0; l < n; l++)
    {
        printf("%4d, ", holdRoute[l]);
        if(l == 10 || l == 20 || l == 30)
        {
            printf("\n");
        }
    }
    printf(" Min: %.2f", sum);
    
}

int tsp(int c, float **matrix, int limit, int *visited_cities, int *costAmount)//code taken from https://sahebg.github.io/computersceince/travelling-salesman-problem-c-program/ and adapated to fit into this program
{
  int count = 0, nearest_city = 999;//999 is the exit variable 
  float minimum = 999;//for first compare
  float temp = 0.0;//hold until confirm min amount
 
  for(count = 0; count < limit; count++)
  {
   
    if((matrix[c][count] != 0) && (visited_cities[count] == 0))//if not self edge and it hasn't been visited yet.
    {
      if(matrix[c][count] < minimum)//if min of that "city"
      {
        minimum = matrix[c][count];//modified this to fit into this program
        temp = matrix[c][count];
        nearest_city = count;
      }
      
    }
  }
  if(minimum != 999)//if not last sequence back to 0 then update cost
  {
    cost = cost + temp;
  }
  return nearest_city;//return
}
 
void minimum_cost(int city, float **matrix, int limit, int *visited_cities, int *costAmount)//part of brute force
{
  int nearest_city = 0;
  visited_cities[city] = 1;//puts city 0 or vertex 0 at starting point
  printf("%d ", city);//prints route starts with vertex 0
  
  nearest_city = tsp(city, matrix, limit, visited_cities, costAmount);//goes to find permuations of every distance from this "city or row in the matrix"
  if(nearest_city == 999)//end case sets up for ending
  {
    nearest_city = 0;
    printf("%d", nearest_city);//prints last return to 0
    cost = cost + matrix[city][nearest_city];//update final cost
    return;
  }
  minimum_cost(nearest_city, matrix, limit, visited_cities, costAmount);//recursion for checking each city or vertex
}

int main (int argc, int argv) 
{
    double trialsTime_max = 5; // in seconds
    long long int trialsCount_max = 1, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 20, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdLastTime = 0, holdTime = 0, expected = 0;
    srand(time(0));
    
    char N_num[] = "N";
    char time[] = "Time";
    char doubling[] = "Doubling Ratio";
    char expDoubling[] = "Expected Ratio";
    double holdingLastN[100000];

	// If you are printing a results table directly, print your header line here.
	printf("Exact Brute Force - n = 4 start - Iterate\n");
    printf("| %-15s | %-15s | %-15s | %-15s |\n", N_num, time, doubling, expDoubling);
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=4; n<N_max; n++ ) 
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
        //printf("N = %d - Correctness Testing\n\n", n);
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/
            float* x;
            float* x2;
            float* y; 
            float* y2;
            int* visited_cities;
            int* costAmount;
            float pi = 22.0/7.0;
            float fr;
            
            int maxValue = 100;
            int radius = 100;
            float stepAngle = (2*pi)/n;
            visited_cities = calloc(n, sizeof(int));
            costAmount = calloc(n, sizeof(int));
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
                //printf("Vertex: %d  x: %.2f   y: %.2f\n", k, x[k], y[k]);
            }
            //printf("\n\n\n");
            float **costMatrix = generateRandomCostMatrix(n, maxValue);
            float **vertex = generateVertex(n, radius, x, y);
            
            float **circularDistance = generateCircEucDistance(n, vertex);
            float **randomEucDistance = generateRandomEucDistance(n, x2, y2);
            printf("After vertex mixup\n");
            for(int i = 0; i < n; i++)
            {
                printf("Vertex: %.0f x: %.2f  y: %.2f\n", vertex[i][2], vertex[i][0], vertex[i][1]);
            }
            printf("\n\n\n");
            for(int g = 0; g < n; g++)
            {
                for(int h = 0; h < n; h++)
                {
                    printf("%8.2f", costMatrix[g][h]);
                    
                    
                        //printf("Distance from coord: %.0f(%.2f, %.2f) to %.0f(%.2f, %.2f) is: %.2f\n", vertex[g][2], vertex[g][0], vertex[g][1], vertex[h][2], vertex[h][0], vertex[h][1], circularDistance[g][h]);
                    
                    
                }
                printf("\n");
            }
            printf("\n\n\n");
            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //greedyAlgCircEuc(n, vertex, circularDistance);
            //greedyAlg(n, vertex, circularDistance);
            //greedyAlg(n, vertex, randomEucDistance);
            minimum_cost(0, costMatrix, n, visited_cities, costAmount);
            printf("\n");
            printf("cost: %.2f", cost);
            printf("\n\n");
            /******* do any "clean up" after running your algorithm ********/
            for(int i = 0; i < n; i++)
            {
                free(costMatrix[i]);
                free(vertex[i]);
                free(circularDistance[i]);
                free(randomEucDistance[i]);
                
            }
            
            free(costMatrix);
            free(vertex);
            free(circularDistance);
            free(randomEucDistance);
            free(x);
            free(x2);
            free(y);
            free(y2);
            free(visited_cities);
            free(costAmount);
            
            cost = 0;
            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        trialSetCount = trial; // value of trial when loop ends is how many we did
        trialSetTime = splitTime; // total time for trial set is the last split time
        averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead
        printf("trialsetcount: %.2f, trialsettime: %.2f\n", trialSetCount, trialSetTime);
        /********* NOW DO A "DUMMY" TRIAL SET TO ESTIMATE THE OVERHEAD TIME ********/
        /* We can just repeat this trialSetCount times, which we know should be faster than above */
        
        splitTime=0.0;
        // get timestamp before set of dummy trials are run:
        trialSetStart = clock();
        for ( trial=0; trial < trialSetCount  && splitTime < trialsTime_max; trial++) 
        {

            /******** any preparations, test input generation, for a single trial run *********/
            /*float* x;
            float* x2;
            float* y; 
            float* y2;
            float pi = 22.0/7.0;
            float fr;
            int* visited_cities;
            int* costAmount;
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
               
            }
            
            float **costMatrix = generateRandomCostMatrix(n, maxValue);
            float **vertex = generateVertex(n, radius, x, y);
            float **circularDistance = generateCircEucDistance(n, vertex);
            float **randomEucDistance = generateRandomEucDistance(n, x2, y2);*/
            /**** DO NOT Call the algorithm function!!! ******/
            
            /******* do any "clean up" after running your algorithm ********/
            /*for(int i = 0; i < n; i++)
            {
                free(costMatrix[i]);
                free(vertex[i]);
                free(circularDistance[i]);
                free(randomEucDistance[i]);
                
            }
            
            free(costMatrix);
            free(vertex);
            free(circularDistance);
            free(randomEucDistance);
            free(x);
            free(x2);
            free(y);
            free(y2);
            free(visited_cities);
            free(costAmount);
            
            cost = 0;*/
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
        //holdTime = estimatedTimePerTrial/holdLastTime; 
        //holdLastTime = estimatedTimePerTrial;
        double expDR;
        int nhalf = n/2;
        //expDR = (pow(n,2)*log2(n))/(pow(nhalf,2)*log2(n/2));
        expDR = (tgamma(n+1))/(tgamma(nhalf+1));
        holdingLastN[n] = estimatedTimePerTrial;
        if(n >= 8)
        {
            
            holdTime = (estimatedTimePerTrial)/(holdingLastN[nhalf]);
            if(n%2 != 0)
            {
                expDR = 0;
                holdTime = 0;
            }
        }
        
        //printf("| %-15d | %-15.10llf | %-15.10llf | %-15f | %15d |\n", n, estimatedTimePerTrial, holdTime, expDR, trialSetCount);
        //trialsCount_max = ceil(trialsCount_max/2);//slowing down trial counts when getting into large N's
        /*if(trialsCount_max < 1)
        {
            trialsCount_max = 1;
        }*/
       
    }
}

