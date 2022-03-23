#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

long long int busyCount = 0;
long long int holdI = 0;
void doBusyWork()
{
    for(int x=0; x<1000; x=x+1)
    {

    }
    busyCount = busyCount+1;
}

void linearFunction(int N)
{
    for(int i=0; i<N; i++)
    {
        doBusyWork();
    }
}
void npow3(int N)
{
    for(int i = 0; i<2*N-6; i++)
    {
        for(int j =0; j< i-5; j++)
        {
            for(int k = j; j>=0; k--)
            {
                doBusyWork();
            }
        }
    }
}
void nlogn(int N)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 1; j<i; j= 2*j)
        {
            doBusyWork();
        }
    }
}
void logn(int N)
{
    if(N>1)
    {
        logn(N/2);
    }
    doBusyWork();
    return; 
}

void n2logn(int N)
{
    if(N>1)
    {
        n2logn(N/2);
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            doBusyWork();
        }
    }   
    return;
}
void npow6(int N)
{
    for(int i = 0; i<N; i++)
    {
        for(int j =0; j<=i; j++)
        {
            for(int k = 0; k<=j; k++)
            {
                for(int a = 0; a<=k; a++)
                {
                    for(int b = 0; b<=a; b++)
                    {
                        for(int c = 0; c<=b; c++)
                        {
                            doBusyWork();
                        }
                    }
                }
            }
        }
    }
}

void logn2(int N)
{
    if(N>1)
    {
        logn2(N/2);
    }
    if(N>1)
    {
        logn2(N/2);
    }
    doBusyWork();
    return; 
}

void exp2N(int N)
{
    if(N<1)
    {
        return;
    }
    if(N>1)
    {
        exp2N(N-1);
    }
    if(N>1)
    {
        exp2N(N-1);
    }
    doBusyWork();
}
void nfact(int N)
{
    for(int i = 0; i<N; i++)
    {
        nfact(N-1);
    }
    doBusyWork();
}


int main (int argc, int argv) 
{
    double trialsTime_max = .250; // in seconds
    double holdExpTime[4100] = {0};
    long long int trialsCount_max = 10000, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = 4097, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdTime = 0, expected = 0, mtbc = 0, holdLastTime = 0;
    char pow2[] = "N^2";
    char N[] = "N";
    char Time[] = "Measured Time";
    char Doubling[] = "Doubling Ratio";
    char ExpDoubling[] = "Expected Doubling Ratio";
    char busy[] = "Busy Count";
    char msbc[] = "Measured Time/Busy Count";
	// If you are printing a results table directly, print your header line here.
    printf("\n\nN!\n\n");
	printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", pow2, N, Time, Doubling, ExpDoubling, busy, msbc);
    printf("________________________________________________________________________________________________________________________________________________\n");
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=1; n<N_max; n=1+n )//n=1+n for 2^n and N!, for all others n=2*n
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
            linearFunction(n); //linear
            //npow3(n); //n^3
            //nlogn(n); //n*log(n)
            //logn(n); //log(n)
            //n2logn(n); //n^2*log(n)
            //npow6(n); //n^6
            //logn2(n); //log(n)^2
            //exp2N(n); //2^n
            //nfact(n); //factorial
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
        expected = (2*n)/n;//linear
        //expected = (pow(n,2))/(pow(n/2,2));//n^2 expected time
        //expected = (pow(n,3))/(pow(n/2,3)); //n^3 expected time
        //expected = (pow(n,6))/(pow(n/2,6)); //n^6 expected time
        //expected = (n*log(n))/(n/2*log(n/2));//nlog(n) expected time
        //expected = (log(n))/(log(n/2));//log(n) expected time
        //expected = (pow(n,2)*log(n))/((pow(n/2,2))*log(n/2)); //n^2*log(n) expected time
        //expected = (pow(log(n),2))/(pow(log(n/2),2)); //log(n)^2 expected time
        /*if(n%2==0)//for the 2^n and N! problems comment out if doing other problems
        {
            int qhold = n/2;
            holdTime = holdExpTime[qhold];
        }
        else
        {
            holdTime = 0;
        }*/
        //expected = (2*pow(2,n)/pow(2,n)); //2^n expected time comment out if doing other problems
        //expected = 0; //n! expected time not sure, comment out if doing other problems??
        //holdExpTime[n] = estimatedTimePerTrial;//for the 2^n and N! problems
        mtbc = estimatedTimePerTrial/busyCount;
        printf("| %-15d | %-15lld |  %-14f | %-15f | %-23f | %-15lld | %-24e |\n", logN, n, estimatedTimePerTrial, holdTime, expected, busyCount, mtbc);
    }
    printf("\n\n\n\n");
}
