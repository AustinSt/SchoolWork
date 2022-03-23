#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int cost = 0;

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
int tsp(int c, float **matrix, int limit, int *visited_cities, int *costAmount)//code taken from https://sahebg.github.io/computersceince/travelling-salesman-problem-c-program/ and adapated to fit into this program
{
  int count = 0, nearest_city = 99999;//999 is the exit variable 
  float minimum = 99999;//for first compare
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
  if(minimum != 99999)//if not last sequence back to 0 then update cost
  {
    cost = cost + temp;
  }
  return nearest_city;//return
}
 
void minimum_cost(int city, float **matrix, int limit, int *visited_cities, int *costAmount)//part of brute force
{
  int nearest_city = 0;
  visited_cities[city] = 1;//puts city 0 or vertex 0 at starting point
  //printf("%d ", city);//prints route starts with vertex 0
  
  nearest_city = tsp(city, matrix, limit, visited_cities, costAmount);//goes to find permuations of every distance from this "city or row in the matrix"
  if(nearest_city == 99999)//end case sets up for ending
  {
    nearest_city = 0;
    //printf("%d", nearest_city);//prints last return to 0
    cost = cost + matrix[city][nearest_city];//update final cost
    return;
  }
  minimum_cost(nearest_city, matrix, limit, visited_cities, costAmount);//recursion for checking each city or vertex
}

int main (int argc, int argv) 
{
    double trialsTime_max = 0.25; // in seconds
    long long int trialsCount_max = 100000, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 20, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;

	// If you are printing a results table directly, print your header line here.
	
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=4; n<N_max; n++)
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
        
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/
            int* visited_cities;
            int maxValue = 1000;
            int* costAmount;
            visited_cities = calloc(n, sizeof(int));
            costAmount = calloc(n, sizeof(int));
            float **costMatrix = generateRandomCostMatrix(n, maxValue);
            /*for(int i = 0; i<n;i++)
            {
              for(int k = 0; k < n; k++)
              {
                printf("%-8.2f",costMatrix[i][k]);
              }
              printf("\n");
            }
            printf("\n\n");*/
            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            minimum_cost(0, costMatrix, n, visited_cities, costAmount);
            //printf("\n\n");
            //printf("cost: %d\n\n", cost);
            /******* do any "clean up" after running your algorithm ********/
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

        printf("%d, %-15.10f\n", n, estimatedTimePerTrial);
        
        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

    }
}
