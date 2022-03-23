// CSC 410
// Starting sample file:  Wed 8/26

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMT 7

void *sayhi( void *param)
{
    long myid;
    myid = (long) param;
    long myret = 100 + myid * 10 + myid;

    printf("Hi from thread %ld\n", myid);
    pthread_exit( (void *) myret );
}

int main()
{
    long i;
    void *status;
    pthread_t  tid[NUMT];

    printf("In main: time to build threads\n");

    for(i = 0; i < NUMT; i++ )
    {
        printf(" Creating %ld\n", i);

        pthread_create( &tid[i], NULL, sayhi, (void *)i);
    }

    printf("In main: all threads created\n");

    long rcode;
    for(i = 0; i < NUMT; i++)
    {
        pthread_join( tid[i], &status );
        rcode = (long) status;
        printf("   Main: joined %d with code %ld\n", i,rcode);
    }

    printf("In main:  all threads joined\n");

    return 0;
}