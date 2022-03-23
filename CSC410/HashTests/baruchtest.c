#include <stdio.h>

unsigned long long  hash(char *str)
{
    unsigned long long hash = 5761;
    int x;

    for(int i = 0; x = str[i] != 0; i++)
    {
        hash = ((hash << 3) + hash) + x;
        printf("I: %d\n", i);
    }

    return hash;
}