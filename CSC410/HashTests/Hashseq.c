#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long hash(char *str);

#define LEN 2

int main(int argc, char *argv[])
{
    char alphabet[] = {"abcdefghijklmnopqrstuvwxyz"};
    //'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'
    //,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,!,@,#,$,%,^,&,*,(,)
    int alphaLen = 5;
    unsigned long long ans;
    char hold[2];
    int holdletter;
    unsigned long long holdArg = strtoull(argv[1], NULL, 10);



    printf("%llu", holdArg);
    for(int i = 0; i < alphaLen; i++)
    {
        for(int k = 0; k < alphaLen; k++)
        {
            holdletter = alphabet[i];
            printf("Letter %c\n", holdletter);
            hold[0] = holdletter;
            holdletter = alphabet[k];
            hold[1] = holdletter;
            //printf("%4c %4c     ", hold[0], hold[1]);
            ans = hash(hold);
            printf("hash ans: %llu\n", ans);
            if(ans == holdArg)
            {
                printf("Answer is %4c %4c", hold[0], hold[1]);
                break;
            }

        }
    }

    
    return 0;
}