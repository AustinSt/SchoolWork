#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <climits>
#include <bits/stdc++.h>
using namespace std;

float **generateVertex(int n, int radius, float *x, float *y)//generates random vertex for circular euc graph
{
    
    //int* list;//for swap
    int *list = new int(n);
    //list = calloc(n, sizeof(int));
    
    //float **vertexp; 
    //vertexp = malloc(n * sizeof(*vertexp));
    float **vertexp = new float*[n];
    for(int i = 0; i < n; i++)
    {
        //vertexp[i] = malloc(n*sizeof(vertexp[0]));
        vertexp[i] = new float[n];
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
    //float **distancep; 
    //distancep = malloc(n * sizeof(*distancep));
    float **distancep = new float*[n];
    for(int i = 0; i < n; i++)
    {
        //distancep[i] = malloc(n*sizeof(distancep[0]));
        distancep[i] = new float[n];    
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

int travllingSalesmanProblem(int n, float **graph, int s)
{
    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < n; i++)
        if (i != s)
            vertex.push_back(i);
 
    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    do {
 
        // store current Path weight(cost)
        int current_pathweight = 0;
 
        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            //cout << vertex[i] << endl;
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
            //cout << "K: " << k << "  currentpath " << current_pathweight << endl;
        }
        current_pathweight += graph[k][s];
        
        // update minimum
        cout << " " << k  << " " << s << " " << graph[k][s] << " " << vertex[s] << endl;

        min_path = min(min_path, current_pathweight);
        cout << "min " << min_path << endl;
 
    } while (
        next_permutation(vertex.begin(), vertex.end()));
    for(int i = 0; i < n; i++)
    {
        cout << " " <<  vertex[i]  << "  ";
    }
    return min_path;
}

int main () 
{
    double trialsTime_max = .250; // in seconds
    long long int trialsCount_max = 1, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 1, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;

	// If you are printing a results table directly, print your header line here.
	
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=1; n<N_max; n=2*n ) 
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
        
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/
            //float* x;
            //float* x2;
            //float* y; 
            //float* y2;
            //int* visited_cities;
            //int* costAmount;
            float pi = 22.0/7.0;
            float fr;
            
            int maxValue = 100;
            int radius = 100;
            float stepAngle = (2*pi)/n;
            //visited_cities = calloc(n, sizeof(int));
            //costAmount = calloc(n, sizeof(int));
            float *x = new float(n);
            float *y = new float(n);
            //x = calloc(n, sizeof(float));//for circ euc graph
            //y = calloc(n, sizeof(float));//for circ euc graph
            //x2 = calloc(n, sizeof(float));//for random euc graph
            //y2 = calloc(n, sizeof(float));//for random euc graph
            for(int j = 0; j < n; j++)
            {
                fr = (float)rand()/(float)(RAND_MAX/maxValue);
                //x2[j] = fr;
                fr = (float)rand()/(float)(RAND_MAX/maxValue);
                //y2[j] = fr;
            }
            for(int k = 0; k < n; k++)
            {
                x[k] = radius * sin(k * stepAngle);
                y[k] = radius * cos(k * stepAngle);
                //printf("Vertex: %d  x: %.2f   y: %.2f\n", k, x[k], y[k]);
            }
            //printf("\n\n\n");
            //float **costMatrix = generateRandomCostMatrix(n, maxValue);
            float **vertex = generateVertex(n, radius, x, y);
            
            float **circularDistance = generateCircEucDistance(n, vertex);
            //float **randomEucDistance = generateRandomEucDistance(n, x2, y2);
            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            cout << travllingSalesmanProblem(n, circularDistance, 0) << endl;
            /******* do any "clean up" after running your algorithm ********/
            delete(x);
            delete(y);
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
