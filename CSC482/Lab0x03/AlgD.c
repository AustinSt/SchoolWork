#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>



int algRun = 0;

int algorithm_D(int N, int code)
{
    //printf("Code: %d  N: %d\n", code, N);
    if(N<=1)
    {
        return 1;
    }
    else
    {
        algRun++;
        return (algorithm_D(N-1, 1) + algorithm_D(N-2, 2));
    }
}


int main (int argc, int argv) 
{
    double trialsTime_max = .250; // in seconds
    double holdExpTime[1000] = {0};
    long long int trialsCount_max = 100000, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 1000, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdTime = 0, expected = 0, mtbc = 0, holdLastTime = 0;
    char pow2[] = "N^2";
    char N[] = "N";
    char Time[] = "Measured Time";
    char Doubling[] = "Doubling Ratio";
    char ExpDoubling[] = "Expected Doubling Ratio";
    char AlgCallC[] = "Alg Call";
    int code = 0;
	// If you are printing a results table directly, print your header line here.
    printf("\n\nAlgorithm D\n\n");
	printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", pow2, N, Time, Doubling, ExpDoubling, AlgCallC);
    printf("________________________________________________________________________________________________________________________________________________\n");
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=1; n<N_max; n=1+n )
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
        
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //*****Comment out which function you want*****//
           
            algorithm_D(n, code);
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
        expected = (2*pow(2,n))/(pow(2,n));
    
        if(n%2==0)//for the 2^n
        {
            int qhold = n/2;
            holdTime = holdExpTime[qhold];
        }
        else
        {
            holdTime = 0;
        }
        holdExpTime[n] = estimatedTimePerTrial;
        printf("| %-15d | %-15lld |  %-14.10f | %-15.10f | %-23f | %-14d |\n", logN, n, estimatedTimePerTrial, holdTime, expected, algRun);
        algRun = 0;
    }
    printf("\n\n\n\n");
}
