#include <stdio.h>
#include <string.h>
#include <math.h>
unsigned long long hash(char *hash)
{
    unsigned long long ans; 
    unsigned long long holdlast = 0;
    size_t len = strlen(hash);
    //printf("LEN: %d\n", len);
    for(int i = 0; i < len; i++)
    {
        ans = hash[i];
        ans = ans*ans*ans;
        ans = 178043*ans + holdlast;
        holdlast = ans;
        ans = holdlast*hash[i];
        //printf("hash: %d\n", hash[i]);
        //printf("2nd ans: %llu\n", ans);
       // printf("%d\n", i);
        
    }


    return ans;

}