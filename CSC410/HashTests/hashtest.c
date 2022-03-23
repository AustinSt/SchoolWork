#include <stdio.h>
#include <string.h>
//#include <unistd.h>

unsigned long long hash(char *str);

int main()
{
    unsigned long long ans;
    char stuff[] = "cat";
    //printf("%c  %c\n", stuff[0], stuff[1]);
    ans = hash(stuff);
    printf("%llu\n", ans);

    return 0;
}