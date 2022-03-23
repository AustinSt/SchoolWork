#include <stdio.h>
#include <stdlib.h>
int counter = 0;
int counter2 = 0;
float mini = 999;
int holdArray[1000];

//function to print the array
float printarray(int arr[], int size, int graph[][4], float **holdCost, float min)//return the added amount or put into global then compare
{
    int i,j;
    float temp = 0;
    float temp2 = 0;
    int flag = 0;
    float **tempholdCost;
    tempholdCost = malloc(size * sizeof(*tempholdCost));
    printf("mini first: %.2f\n", mini);
    for(int i = 0; i < size; i++)
    {
        tempholdCost[i] = malloc(size*sizeof(tempholdCost[0]));
    }
    
    for(i=0; i<size; i++)
    {
        //printf(" %d ",arr[i]);
        //printf("%d ", graph[arr[i]][i]);
        //printf("%d ", graph[i][arr[i]]);
        if(graph[arr[i]][i] == 0)
        {
            flag = 1;
        }
        
    }
    if(flag == 0)
    {
        for(i = 0; i < size; i++)
        {
            temp = temp + graph[arr[i]][i];
            temp2 = temp + graph[i][arr[i]];
            tempholdCost[counter][i] = arr[i];
            //printf("temp: %.2f  route: %.2f ", temp, tempholdCost[counter][i]);
        }
       
    }
    if(temp < mini && flag == 0)
    {
        mini = temp;
        for(i = 0; i < size; i++)
        {
            holdArray[i+1] = arr[i];
            printf(" %d ",holdArray[i]);
        }
        printf("\n");
        printf("temp: %.2f  min: %.2f\n  ", temp, mini);
    }
    printf("\n");
    //counter++;
    return min;
}

//function to swap the variables
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
float permutation(int *arr, int start, int end, int graph[][4], float **holdCost, float min)
{
    float temp = 0;
    if(start==end)
    {
        
            min = printarray(arr, end+1, graph, holdCost, min);
       
        
        
        return min;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end, graph, holdCost, min);
        swap((arr+i), (arr+start));
    }
}

int main()
{
    //taking input to the array
    int size = 4;
    float min = 9999;
    
    //int *holdCost[]
    float **holdCost;
    holdCost = malloc(size * sizeof(*holdCost));
    for(int i = 0; i < size; i++)
    {
        holdCost[i] = malloc(size*sizeof(holdCost[0]));
    }
    
    int graph[4][4] = { { 0, 15, 30, 20 },
                       { 15, 0, 35, 25 },
                       { 30, 35, 0, 30 },
                       { 20, 25, 30, 0 } };
    /*int graph[4][4] = { { 0, 1, 2, 3 },
                       { 4, 0, 5, 6 },
                       { 7, 8, 0, 9 },
                       { 10, 11, 12, 0 } };*/
    /*int graph[3][3] = {{ 0, 1, 2},
                        {3, 0, 4},
                        {5, 6, 0}};*/
    
    int i;
    int arr[size];
    for(i=0;i<size;i++)
    {
        arr[i] = i;
        //printf("%d\n", graph[i][1]);
    }
        
    //calling permutation function
    min = permutation(arr, 0, size-1, graph, holdCost, min);
    for(int i = 0; i < size+1; i++)
    {
        printf(" %d ", holdArray[i]);
    }
    printf("temp: %.2f", mini);
    free(holdCost);
    return 0;
}