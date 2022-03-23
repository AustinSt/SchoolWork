#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int visited_cities[2097152];
float cost = 0;
int costAmount[2097152];

int tsp(int c, float **matrix, int limit)
{
  int count, nearest_city = 999;
  int minimum = 999;
  float temp;
  for(count = 0; count < limit; count++)
  {
    if((matrix[c][count] != 0) && (visited_cities[count] == 0))
    {
      if(matrix[c][count] < minimum)
      {
        minimum = matrix[count][0] + matrix[c][count];
      }
      temp = matrix[c][count];
      nearest_city = count;
    }
  }
  if(minimum != 999)
  {
    cost = cost + temp;
  }
  return nearest_city;
}
 
void minimum_cost(int city, float **matrix, int limit)
{
  int nearest_city;
  visited_cities[city] = 1;
  printf("%d ", city);
  nearest_city = tsp(city, matrix, limit);
  if(nearest_city == 999)
  {
    nearest_city = 0;
    printf("%d", nearest_city);
    cost = cost + matrix[city][nearest_city];
    return;
  }
  minimum_cost(nearest_city, matrix, limit);
}

int main()
{
    int n = 6;
    int maxValue = 100;
    srand(time(0));
    int radius = 100;
    
    float* x;
    float* y;
    float pi = 22.0/7.0;
    float stepAngle = (2*pi)/n;
    printf("stepAngle %.10f\n", stepAngle);
    float fr;
 
    x = calloc(n, sizeof(float));
    y = calloc(n, sizeof(float));
    float **distance;
    distance = malloc(n*sizeof(*distance));
    for(int i = 0; i < n; i++)
    {
        distance[i] = malloc(n*sizeof(distance[0]));
    }
    float **vertex;
    vertex = malloc(n*sizeof(*vertex));
    for(int i = 0; i < n; i++)
    {
        vertex[i] = malloc(n*sizeof(vertex[0]));
    }
    
    
    for(int k = 0; k < n; k++)
    {
        x[k] = radius * sin(k * stepAngle);
        y[k] = radius * cos(k * stepAngle);
        printf("Vertex: %d  x: %.2f   y: %.2f\n", k, x[k], y[k]);
    }
    vertex[0][0] = x[0];
    vertex[0][1] = y[0]; 
    vertex[0][2] = 0;
    int list[n];
    for(int i = 1; i < n; i++)
    {
        list[i] = i;
        vertex[i][2] = i;
    }
    size_t a;
    
    for(a = 1; a < n; a++)
    {
        size_t j = a + rand() / (RAND_MAX / (n-a)+1);
        int t = list[j];
        list[j] = list[a];
        list[a] = t;
        vertex[list[a]][0] = x[a];
        vertex[list[a]][1] = y[a];
        vertex[list[a]][2] = a;
        //printf("list[a] %d\n", list[a]); 
        //printf("x: %.2f   y: %.2f    vertex : %.2f  %.2f\n", x[a], y[a], vertex[list[a]][0], vertex[list[a]][1]);
         
    }
    printf("\n\n\n");
    for(int k = 0; k < n; k++)
    {
        for(int z = 0; z < n; z++)
        {
            if(k == z)
            {
                distance[k][z] = 0;
            }
            else
            {
                distance[k][z] = pow((pow(vertex[k][0]-vertex[z][0],2)+pow(vertex[k][1]-vertex[z][1],2)),0.5);
            }
            
        }
    }
    for(int i = 0; i < n; i++)
    {
        printf("Vertex: %.0f  x:  %.2f   y:  %.2f\n", vertex[i][2], vertex[i][0], vertex[i][1]);
    }
    printf("\n\n\n");
    for(int g = 0; g < n; g++)
    {
        for(int h = 0; h < n; h++)
        {
            
            //printf("Distance from coord: (%.2f, %.2f) to (%.2f, %.2f) is: %.2f\n", vertex[g][0], vertex[g][1], vertex[h][0], vertex[h][1], distance[g][h]);
            printf("%8.2f", distance[g][h]);
            
        }
        printf("\n");
    }
    minimum_cost(0, distance, n);
    printf("\n\n\n");
    printf("cost: %.2f\n", cost);
   
}