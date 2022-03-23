#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//#include<unistd.h>
#include <omp.h>


#define STRLEN 4
#define THRD 4
unsigned long long hash(char *str);
unsigned long long hashInput; //Hold input hash string
//unsigned long long resHash; //Hold result hash string

/* This variable holds string case.
1 = search in upper case and/or number string alone.
2 = search in lower case and/or number string alone.
0 = uppercase lower case and number string */
int search = 2;

// Generate all possibel combinations of string,
//get hashcode from hash() and compare with input hash
char* generate(char* arr, int sl, int len)
{
    unsigned long long int mxLoop = pow(len, sl); //max possible combination of string
    unsigned long long int i;
    
    static char holdstr[STRLEN];
    int flag = 0;
    omp_set_num_threads(THRD);

    #pragma omp parallel for schedule(dynamic) collapse(1)
    for (i=0; i<mxLoop; i++) 
    {
        if(flag == 1) continue;
        static char str[STRLEN];
        unsigned long long resHash;
        int rsl = sl - 1;
        int val = i;
        for (int j = 0; j < sl; j++) {
            if(flag == 1) continue;
            int pos = val % len;
            str[rsl] = arr[pos];
            rsl--;
            val = val / len;
        }
        printf("%s \n", str);
        
        resHash = hash(str);
        if (hashInput == resHash)
        {
            strcpy(holdstr, str);
            flag = 1;
        }        
        
    }   
    return holdstr;
}

// driver function
int main(int argc, char *argv[])
{
        char arrLc[] = {'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};
    char arrUp[] = {'A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
    char arrUpLw[] = {'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
    int arrLen;

    if (argc < 2) {
        printf("Arguements Missing!!\n");
        printf("First arugement must be hashcode (required)");
        exit(0);
     }

    hashInput = atoll(argv[1]);
        printf("%llu\n", hashInput);

        char * res = "";
    char arr1[36];
    char arr3[62];

    switch (search)
    {
    case 1:
        arrLen = sizeof(arrUp) / sizeof(arrUp[0]);
        res = generate(arrUp, STRLEN, arrLen);
        break;
    case 2:
        arrLen = sizeof(arrLc) / sizeof(arrLc[0]);
        res = generate(arrLc, STRLEN, arrLen);
        break;
    default:
            arrLen = sizeof(arrUpLw) / sizeof(arrUpLw[0]);
            res = generate(arrUpLw, STRLEN, arrLen);
        break;
    }

    printf("result %s \n", res);

    if (res != NULL)
        printf("Hurray found the string! %s\n",res);
    else
        printf("String not found!\n");

    return 0;
}