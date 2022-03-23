#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


#define FORCED 3
#define MAX_N 65
//67108865
#define MAX_V 100


long long int* ptr;
long long int* holdTriplets;
long long int foundTrip[1000][3];
int count = 0;
int count1 = 0;
void shuffle(long long int n)//for small verification tests, takes arr and iterates negating even numbers and then shuffles the array also prints values in array
{
    for(int i = 0; i < n; i++)//verfication tests
    {
        if(i%2==0)
        {
            ptr[i] = i+1;
        }
        else
        {
            ptr[i] = (i+1)*-1;
        }
    }
    
    for(int i = 0; i < n-1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (n-i)+1);
        int t = ptr[j];
        ptr[j] = ptr[i];
        ptr[i] = t;
    }
    printf("\n-----------------------------\n"); //for printing out values
    printf("N: %d\n\n", n);
    printf("Values in Array: (");
    for(int k = 0; k < n; k++)
    {
        printf(" %lld ,", ptr[k]);
    }
    printf(")\n\n\n");
}
void print()//for small verification examples, prints out array holding triplets found
{
    printf("Triplet Sums Found: ");
    for(int z = 0; z < count; z++)
    {
        printf(" (%lld , %lld, %lld) |", foundTrip[z][0], foundTrip[z][1], foundTrip[z][2]);
    }
}
void generateTriSumTestInput(long long int holdArr[], long long int arrSize, int maxValue, int nForcedTriplets)//for force triplets
{
    int* holdElements;
    int forcedHold;
    int forcedTripleElement;
    holdElements = calloc(nForcedTriplets*4, sizeof(int));
    int i;
    for(i = 0; i < arrSize; i++)
    {
        holdArr[i] = rand() % maxValue - maxValue/2;
    }
    if(nForcedTriplets > 0)//max 3 forced triplets to avoid collisions
    {
        
        for(int k = 0; k<3; k++)//fills in second array of elements for the holdArr
        {
            forcedTripleElement = rand()%arrSize;
            holdElements[k] = forcedTripleElement;
            if(arrSize < 17)
            {
                holdElements[0] = 1;
                holdElements[1] = 2; 
                holdElements[2] = 3; 
            }
            
        }
        if(holdArr[holdElements[0]]+holdArr[holdElements[1]]+holdArr[holdElements[2]] != 0)//if already 0 then skip
        {
            forcedHold = holdArr[holdElements[0]] + holdArr[holdElements[1]];//adds up
            forcedHold = forcedHold * -1;//takes the neg
            holdArr[holdElements[2]] = forcedHold;//put its back in
        }
        if(nForcedTriplets > 1 && arrSize > 18)
        {
            if(nForcedTriplets > 1)
            {
                if(holdArr[holdElements[3]]+holdArr[holdElements[4]]+holdArr[holdElements[5]] != 0)//if already 0 then skip
                {
                    forcedHold = holdArr[holdElements[3]] + holdArr[holdElements[4]];
                    forcedHold = forcedHold * -1;
                    holdArr[holdElements[5]] = forcedHold;
                }
            }
            if(nForcedTriplets > 2)
            {
                if(holdArr[holdElements[6]]+holdArr[holdElements[7]]+holdArr[holdElements[8]] != 0)//if already 0 then skip
                {
                    forcedHold = holdArr[holdElements[6]] + holdArr[holdElements[7]];
                    forcedHold = forcedHold * -1;
                    holdArr[holdElements[8]] = forcedHold;
                }
            }
        }
    }
    
}

void selectionSort(long long int n)//sorting algorithm
{
    int i, j, min, temp;

    for(int i = 0; i < n-1; i++)
    {
        min = i;
        for(j = i + 1; j < n; j++)
        {
            if(ptr[j] < ptr[min])
            {
                min = j;
            }
        }
        
        temp = ptr[min];
        ptr[min] = ptr[i];
        ptr[i] = temp;
    }
    
}

int bruteForce(long long int arr[], long long int n)//brute force at n^3
{
    for(int i = 0; i < n-3; i++)
    {
        for(int k= i+1; k < n-2; k++)
        {
            for(int j = k+1; j < n-1; j++)
            {
                if(arr[i]+arr[k]+arr[j] == 0)
                {
                    
                    //printf("Found a triplet sum: %d, %d, %d\n", arr[i],arr[k],arr[j]); //for printing out sums that are found
                    foundTrip[count][0] = arr[i];
                    foundTrip[count][1] = arr[k];
                    foundTrip[count][2] = arr[j];
                    count++;
                    //return 1;
                }
            }
        }
    }
    
    return 0;
}

void fasterAlgTest1(long long int n)//bad algorithm did not work as intended 
{
    
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j< n; j++)
        {
            if(ptr[i]+ptr[j]+ptr[n] == 0)
            {
                foundTrip[count][0] = ptr[i];
                foundTrip[count][1] = ptr[j];
                foundTrip[count][2] = ptr[n];
                count++;
            }
        }
    }
    if(n > 1)
    {
        fasterAlgTest1(n-1);
    }
}

void fasterAlgTest2(long long int n)//also failed algorithm does not work
{
    int l = 0;
    int r = n - 1;
    int count1 =0, count2 = 0, count3 = 0;
    for(int i = 0; i < n-1; i++)
    {
        count1++;
        for(int j = i+1; j< n; j++)
        {
            count2++;
            //l = 0;
            //r = n -1;
            while(l <= r)
            {
                count3++;
                int mid = l + (r-1)/2;
                //printf("i: %d, j: %d Mid: %d, l: %d, r: %d\n",i , j, mid, l, r);
                if(ptr[i]+ptr[j]+ptr[mid] == 0)
                {
                    foundTrip[count][0] = ptr[i];
                    foundTrip[count][1] = ptr[j];
                    foundTrip[count][2] = ptr[mid];
                    //printf("Trips: %lld, %lld, %lld\n", ptr[i], ptr[j], ptr[mid]);
                    count++;
                    return;
                }
                if(ptr[i]+ptr[j]+ptr[mid] < 0)
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            
        }
        
    }
    //printf("Count1: %d  Count 2: %d  Count 3: %d\n", count1, count2, count3);
    
}

int fasterAlgTest(long long int n)//the correct faster Alg at n^2*log(n)
{
    long long int* holdingArr;
    
    
    for(int i = 0; i < n-1; i++)
    {
        holdingArr = calloc(n+1, sizeof(long long int));
        int countarr = 0;
        for(int j = i+1; j< n; j++)
        {
            int x = (ptr[i]+ptr[j])*-1;
            
            if(holdingArr[countarr-1] == x)
            {
                //printf("Trips: %lld, %lld, %lld\n", ptr[i], ptr[j], x);
                foundTrip[count][0] = ptr[i];
                foundTrip[count][1] = ptr[j];
                foundTrip[count][2] = x;
                count++;
            }
            else
            {
                holdingArr[countarr] = ptr[j];
                //printf("Holding: %d\n", holdingArr[countarr]);
                countarr++;
            }
         }
        
        free(holdingArr);
        
    }
    
   
    
}


void fastestAlg(int n)
{

    for(int i = 0; i < n -3; i++)
    {
        int k = 0 - ptr[i];

        int low = i + 1, high = n - 1;

        while(low < high)
        {
            if(ptr[low] + ptr[high] < k)
            {
                low++;
            }
            else if(ptr[low]+ptr[high] > k)
            {
                high--;
            }
            else
            {
                
                foundTrip[count][0] = ptr[i];
                foundTrip[count][1] = ptr[low];
                foundTrip[count][2] = ptr[high];
                count++;
                low++;
                high--;
            }
        }
    }
}



int main (int argc, int argv) 
{
    double trialsTime_max = .250; // in seconds
    long long int trialsCount_max = 1, // increase as needed to avoid time measurements of zero
                  N_min = 1,
                  N_max = MAX_N, // adjust as needed, keep small for debugging
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdTime = 0, expected = 0, holdLastTime = 0;
  
    srand(time(NULL));
    char pow2[] = "N^2";
    char N[] = "N";
    char Time[] = "Measured Time";
    char Doubling[] = "Doubling Ratio";
    char ExpDoubling[] = "Expected Doubling Ratio";
    char TripletSucc[]= "Triplets Found";
    char avgTrialT[] = "Avg Trial Time";
    char dumTime[] = "Avg Dummy Time";
    char trialCount[] = "Num of Trials";
	// If you are printing a results table directly, print your header line here.
    //printf("\n\nSum of Triplets  -  Max Value: %d     -    Number of Forced Triplets:  %d\n\n", MAX_V, FORCED);
	//printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", pow2, N, trialCount, avgTrialT, dumTime, Time, Doubling, ExpDoubling, TripletSucc);
    //printf("_____________________________________________________________________________________________________________________________________________________________________________\n");
	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=4; n<N_max; n=2*n ) 
    {
        /********* any preparations, test input generation, to be used for entire trial set ********/
        
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) 
        {
            /******** any preparations, test input generation, for a single trial run *********/
            ptr = calloc(n, sizeof(long long int));
            holdTriplets = calloc(n, sizeof(long long int));
            
            //generateTriSumTestInput(ptr, n, MAX_V, FORCED);
            shuffle(n);//same list size test **for small list verification**
            selectionSort(n);//sort the list
            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            
            
            bruteForce(ptr, n);//good
            //fasterAlgTest1(n);//defunct
            //fasterAlgTest2(n);//defunct
            //fasterAlgTest(n);//good
            //fastestAlg(n);//good
            /******* do any "clean up" after running your algorithm ********/
            free(ptr);
            free(holdTriplets);
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
            ptr = calloc(n, sizeof(long long int));
            holdTriplets = calloc(n, sizeof(long long int));
            //generateTriSumTestInput(ptr, n, MAX_V, FORCED);
            selectionSort(n);
            /**** DO NOT Call the algorithm function!!! ******/

            /******* do any "clean up" after running your algorithm ********/
            free(ptr);
            free(holdTriplets);
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
        //expected = (n*n*n)/(n/2*n/2*n/2); //n^3 expected time
        
        //expected = (pow(n,2)*log(n))/((pow(n/2,2))*log(n/2)); //n^2*log(n) expected time
        expected = (pow(n,2))/(pow(n/2,2)); //n^2 expected time
        //printf("| %-15d | %-15lld | %-15lld |  %-14.10llf |  %-14.10llf | %-14.10llf | %-15f | %-23f | %-15d |\n", logN, n, trialsCount_max, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial, holdTime, expected, count);
        
        trialsCount_max = ceil(trialsCount_max/2);//slowing down trial counts when getting into large N's
        if(trialsCount_max < 1)
        {
            trialsCount_max = 1;
        }
        
        print();//printing out triplets found for testing
        printf("Count %d\n", count);
        //printf("Count1 %d\n", count1);
        count = 0;
        count1 = 0;
        
    }
}
