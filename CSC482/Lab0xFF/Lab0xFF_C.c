#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int holdArray[1000];
float min = 9999;
int count = 0;
float heursticHold = 0;
void printarray(int arr[], int size, float **graph)//for brute force - return the added amount or put into global then compare
{
    int i;
    float temp = 0;
    
    int flag = 0;//flag for self edges
    
    
    for(i=0; i<size; i++)
    {
        
        if(graph[arr[i]][i] == 0)
        {
            flag = 1;//if hit yes then do not parse this iteration because it is using self edges
        }
        
    }
    if(flag == 0)//good parse
    {
        for(i = 0; i < size; i++)
        {
            temp = temp + graph[arr[i]][i];
            
            
        }
       
    }
    if(temp < min && flag == 0)//checks min
    {
        min = temp;
        for(i = 0; i < size; i++)
        {
            holdArray[i] = arr[i];
            
        }
    }
  
}

//function to swap the variables 
void swap(int *a, int *b)//for brute force
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
void permutation(int *arr, int start, int end, float **graph)//for brute force - idea from https://www.codesdope.com/blog/article/generating-permutations-of-all-elements-of-an-arra/
{
    
    if(start==end)
    {
        
        printarray(arr, end+1, graph);
       
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end, graph);
        swap((arr+i), (arr+start));
    }
}

float **generateVertex(int n, int radius, float *x, float *y)//generates random vertex for circular euc graph
{
    
    int* list;//for swap
    
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
                distancepp[k][z] = 0;
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
            else
            {
                costMatrixp[i][k] = (float)rand()/(float)(RAND_MAX/maxValue);
                costMatrixp[k][i] = costMatrixp[i][k];//copy over to the other side
            }
           
            
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
    sum = sum + min;//prints sum
    heursticHold = sum;//for SQR
    /*printf("Route: 0, ");//for correctness testing
    for(int l = 0; l < n; l++)
    {
        printf("%4d, ", holdRoute[l]);
        if(l == 10 || l == 20 || l == 30)
        {
            printf("\n");
        }
    }
    printf(" Min: %.2f", sum);*/
    
}



int main (int argc, int argv) 
{
    double trialsTime_max = 5; // in seconds
    long long int trialsCount_max = 100000, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 10000, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdLastTime = 0, holdTime = 0, expected = 0;
    srand(time(0));
    
    char N_num[] = "N";
    char time[] = "Time";
    char doubling[] = "Doubling Ratio";
    char expDoubling[] = "Expected Ratio";
    char avgSol[] = "Avg Solution";
    char avgExactSol[] = "Avg Exact Solution";
    char avgSQR[] = "Avg SQR";
    double holdingLastN[100000];
    float holdLastMin[1000];
    float holdLastSum[1000];
    
	// If you are printing a results table directly, print your header line here.
	printf("Greedy - n = 4 start - Iterate\n");
    //printf("Greedy vs Exact Brute Force SQR\n");//for SQR run
    printf("| %-15s | %-15s | %-15s | %-15s |\n", N_num, time, doubling, expDoubling);//for time trial run
    //printf("| %-15s | %-15s | %-15s | %-15s |\n", N_num, avgSol, avgExactSol, avgSQR);//for SQR run
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
            float* x;//for euc graph
            float* x2;//for random euc graph
            float* y; //for euc graph
            float* y2;//for random euc graph
            
            float pi = 22.0/7.0;//pi
            float fr;//holder
            int* arr;//array for brute force
            arr = calloc(n, sizeof(int));
            int maxValue = 100;//this is for random euc distance
            for(int z = 0; z < n; z++)
            {
                arr[z] = z; //fill array for permutation
            }
            int radius = 100;//for radius on circ euc graph
            float stepAngle = (2*pi)/n;//step angle for circ euc graph
            
            x = calloc(n, sizeof(float));//for circ euc graph
            y = calloc(n, sizeof(float));//for circ euc graph
            x2 = calloc(n, sizeof(float));//for random euc graph
            y2 = calloc(n, sizeof(float));//for random euc graph
            for(int j = 0; j < n; j++)//setup for random euc graph
            {
                
                fr = (float)rand()/(float)(RAND_MAX/maxValue);
                x2[j] = fr;
                fr = (float)rand()/(float)(RAND_MAX/maxValue);
                y2[j] = fr;
            }
            for(int k = 0; k < n; k++)//for setting up step angle for circular euc graph
            {
                x[k] = radius * sin(k * stepAngle);
                y[k] = radius * cos(k * stepAngle);
                //printf("Vertex: %d  x: %.2f   y: %.2f\n", k, x[k], y[k]);//correctness testing
            }
            //printf("\n\n\n");
            float **costMatrix = generateRandomCostMatrix(n, maxValue);//generates random cost matrix
            float **vertex = generateVertex(n, radius, x, y);//generates vertices to be used in cirular euc distances
            
            float **circularDistance = generateCircEucDistance(n, vertex);//generates euc distances
            float **randomEucDistance = generateRandomEucDistance(n, x2, y2);//generates random euc distances
            //printf(" N = %d\n", n);
           //printf("After vertex mixup\n");
            for(int i = 0; i < n; i++)//for correctness testing
            {
                //printf("Vertex: %.0f x: %.2f  y: %.2f\n", vertex[i][2], vertex[i][0], vertex[i][1]);
            }
            //printf("\n\n\n");
            /*for(int g = 0; g < n; g++)//for matrix correctness test
            {
                for(int h = 0; h < n; h++)
                {
                    printf("%8.2f", randomEucDistance[g][h]);
                }
                printf("\n");
            }
            printf("\n\n\n");*/
            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            
            //greedyAlg(n, vertex, costMatrix);//greedy alg w/ random cost matrix
            greedyAlg(n, vertex, circularDistance);//greedy alg w/ circ euc distances
            //greedyAlg(n, vertex, randomEucDistance);//greedy alg w/ random euc distance
            
            //permutation(arr, 0, n-1, costMatrix);//brute force alg w/ random cost matrix
            //permutation(arr, 0, n-1, circularDistance);//brute force alg w/ circ euc distance
            //permutation(arr, 0, n-1, randomEucDistance);//brute force alg w/ random euc distance



            //holdLastMin[count] = min;//for SQR
            //holdLastSum[count] = heursticHold;//for SQR
           
            /*for(int i = 0; i < n; i++)//for bruteforce correctness
            {
                printf(" %d ", holdArray[i]);
            }
            printf("   %.2f\n", min);*/
            /******* do any "clean up" after running your algorithm ********/
            for(int i = 0; i < n; i++)//freeing all dynamic arrays
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
            free(arr);
            min = 9999;
            heursticHold = 0;
            //count++;
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
            float* x2;
            float* x3;
            float* y2; 
            float* y3;
            float pi2 = 22.0/7.0;
            float fr2;
            
            int* arr2;
            arr2 = calloc(n, sizeof(int));
            int maxValue = 100;
            for(int z = 0; z < n; z++)
            {
                arr2[z] = z; //fill array with iteration
            }
            
            int radius2 = 10;
            float stepAngle2 = (2*pi2)/n;
            x2 = calloc(n, sizeof(float));//for circ euc graph
            y2 = calloc(n, sizeof(float));//for circ euc graph
            x3 = calloc(n, sizeof(float));//for random euc graph
            y3 = calloc(n, sizeof(float));//for random euc graph
            for(int j = 0; j < n; j++)
            {
                fr2 = (float)rand()/(float)(RAND_MAX/maxValue);
                x3[j] = fr2;
                fr2 = (float)rand()/(float)(RAND_MAX/maxValue);
                y3[j] = fr2;
            }
            for(int k = 0; k < n; k++)
            {
                x2[k] = radius2 * sin(k * stepAngle2);
                y2[k] = radius2 * cos(k * stepAngle2);
               
            }
            
            float **costMatrix2 = generateRandomCostMatrix(n, maxValue);
            float **vertex2 = generateVertex(n, radius2, x2, y2);
            float **circularDistance2 = generateCircEucDistance(n, vertex2);
            float **randomEucDistance2 = generateRandomEucDistance(n, x3, y3);
            /**** DO NOT Call the algorithm function!!! ******/
            
            /******* do any "clean up" after running your algorithm ********/
            for(int i = 0; i < n; i++)
            {
                free(costMatrix2[i]);
                free(vertex2[i]);
                free(circularDistance2[i]);
                free(randomEucDistance2[i]);
                
            }
            
            free(costMatrix2);
            free(vertex2);
            free(circularDistance2);
            free(randomEucDistance2);
            free(x2);
            free(x3);
            free(y2);
            free(y3);
            free(arr2);
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
        double expDR;//expected doubling ratio
        int nhalf = n/2;//for n/2
        //expDR = (pow(n,2)*log2(n))/(pow(nhalf,2)*log2(n/2));//for greedy alg
        expDR = (tgamma(n+1))/(tgamma(nhalf+1));//for n! expected
        holdingLastN[n] = estimatedTimePerTrial;//holds all trial run times
        if(n >= 8)
        {
            
            holdTime = (estimatedTimePerTrial)/(holdingLastN[nhalf]);
            if(n%2 != 0)
            {
                expDR = 0;
                holdTime = 0;
            }
        }
        /*float tempMin = 0;//for SQR
        float tempSum = 0;//for SQR
        float tempAll = 0;//for SQR
        for(int i = 0; i < count; i++)//gets all trial runs for SQR and adds them up
        {
            tempMin += holdLastMin[i];
            
            tempSum += holdLastSum[i];
        }
        
        tempMin = tempMin/count;//SQR - divides by current amounts
        
        tempSum = tempSum/count;//SQR
        tempAll = tempMin/tempSum;//SQR*/
        printf("| %-15d | %-15.8llf | %-15.8llf | %-15.2f |\n", n, estimatedTimePerTrial, holdTime, expDR);//time test
        //printf("| %-15d | %-15.2f | %-15.2f    | %-15.2f |\n", n, tempMin, tempSum, tempAll);//SQR run
        //count = 0;//for SQR
       
    }
}

