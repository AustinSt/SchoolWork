#ifndef __UNION_FIND__H__
#define __UNION_FIND__H__

#include <iostream>

using namespace std;

enum VERIFY_RANGE_ERRORS
{
    VALUES_WITHIN_RANGE = 1,
    NUM_ONE_OUTSIDE_RANGE,
    NUM_TWO_OUTSIDE_RANGE,
    UNDEFINED_ERROR
};

class C_unionFind
{
    public:
        C_unionFind();
        ~C_unionFind();
        void initArray(int);
        VERIFY_RANGE_ERRORS unionNumbers(int, int);
        void isConnected(int, int);
        void printArray();

    private:
        int *p_dataArray;
        int p_arraySize;

        VERIFY_RANGE_ERRORS p_verifyRange(int, int);
        void p_initArray(int);
        void p_unionNumbers(int, int);
        bool p_isConnected(int, int);
        void p_printArray();
};

#endif