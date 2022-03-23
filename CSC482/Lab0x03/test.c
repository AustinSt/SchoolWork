#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 67108865
//67108865
long long int whileCount = 0, aCount = 0, bCount = 0;

double* ptr;
void algorithm_A(int N, double list[])
{
    int a = 0;
    int b = N;
    //printf("Lst N %d\n", list[N]);
    while(a<b)
    {
        whileCount++;
        if(list[a]<list[b])
        {
            //printf("Lst N %d\n", list[a]);
            aCount++;
            a = a + 1;
        }
        else
        {
            //printf("Lst N %d\n", list[b]);
            bCount++;
            b = b - 1;
        }
    }
}

void algorithm_B(long long int N, double list[])
{
    for(long long int q = 1; q<N; q=2*q)
    {
        whileCount++;
        //printf("Number: %d\n", list[q]);
        for(long long int i = 0; i<N-q;i=i+2*q)
        {
            aCount++;
            if(list[i]<list[i+q])
            {
                bCount++;
                int tmp = list[i];
                list[i] = list[i];
                list[i+q] = tmp;
            }
        }
    }
}
void doBusyWork()
{
    whileCount++;
    for(int x=0; x<1000; x=x+1)
    {

    }
    
}
void doublingAlg(int n)
{
    for(int i = 1; i < n; i=i*2)
    {
        doBusyWork();
    }
}
void insideLoop(int n)
{
    int q = 1;
    for(int i = 0; i < n-q; i=i+2*q)
    {
        doBusyWork();
        q=2*q;
    }
}

void nonRecLoop(int n)
{

}
int main (int argc, int argv) 
{
    double trialsTime_max = .250; // in seconds
    
    time_t t;
    long long int trialsCount_max = 1, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = N_MAX, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    size_t sizeArr;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdTime = 0, expected = 0, mtbc = 0, holdLastTime = 0;
    char pow2[] = "N^2";
    char N[] = "N";
    char Time[] = "Measured Time";
    char Doubling[] = "Doubling Ratio";
    char ExpDoubling[] = "Expected Doubling Ratio";
    char whileCountC[] = "While Count";
    char aCountC[] = "A Count";
    char bCountC[] = "B Count";
    srand((unsigned) time(&t));
	// If you are printing a results table directly, print your header line here.
    printf("\n\nAlgorithm A\n\n");
	printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", pow2, N, Time, Doubling, ExpDoubling, whileCountC, aCountC, bCountC);
    printf("________________________________________________________________________________________________________________________________________________\n");
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    
    
    for ( n=1; n<N_max; n=2*n )//n=1+n for 2^n and N!, for all others n=2*n
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
       
        ptr = calloc(n, sizeof(double));
       
        
        for(long long int i = 0 ;i < n; i++)
        {
            ptr[i] = rand()%100;
        }

        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //algorithm_A(n, ptr);
            //algorithm_B(n, ptr);
            //doublingAlg(n);
            insideLoop(n);
            /******* do any "clean up" after running your algorithm ********/
            
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
        int logN = log2(n);
        holdTime = estimatedTimePerTrial/holdLastTime; 
        holdLastTime = estimatedTimePerTrial;
        //expected = log(n)/log(n/2);
        //expected = (2*pow(3,n)/pow(3,n)); //2*2^n
        //expected = (n/2)/((n/2)/2);
        //float holdingNum = n/2;
        //expected = (holdingNum)/((holdingNum)/2);
        expected = 
        printf("| %-15d | %-15lld |  %-14.10llf | %-15f | %-23f | %-15d | %-15d | %-15d |\n", logN, n, estimatedTimePerTrial, holdTime, expected, whileCount, aCount, bCount);
        whileCount = 0;
    }
    printf("\n\n\n\n");
}
