#include "unionFind.h"
#include "customErrorClass.h"


C_unionFind::C_unionFind()
{
    this->p_dataArray = NULL;
    this->p_dataArray = 0;
}
C_unionFind::~C_unionFind()
{
    delete[] this->p_dataArray;
}

void C_unionFind::initArray(int userArraySize)
{
	if(NULL != this->p_dataArray)
    {
        throw MyException("Warning: Cannot initialize array twice; not re-initializing.");
    }
    else
    {
        try
        {
            this->p_initArray(userArraySize);
        }
        catch(MyException &e)
        {
            cout << e.what()<<endl;
        }
        
    }
}



VERIFY_RANGE_ERRORS C_unionFind::unionNumbers(int numOne, int numTwo)
{
	VERIFY_RANGE_ERRORS retValue = UNDEFINED_ERROR;

    retValue = this->p_verifyRange(numOne, numTwo);

    if(NUM_ONE_OUTSIDE_RANGE == retValue)
    {
        throw MyException("ERROR: first value is not within the array range");
    } 
    else if(NUM_TWO_OUTSIDE_RANGE == retValue)
    {
        throw MyException("ERROR: second value is not within the array range");
    }
    else if(UNDEFINED_ERROR == retValue)
    {
        throw MyException("ERROR: unknown problem occured unionNumbers");
    }
    
    if(VALUES_WITHIN_RANGE == retValue)
    {
        this->p_unionNumbers(numOne, numTwo);
    }
    else
    {
        throw MyException("ERROR: Something really weird happened");
    }
    

}

void C_unionFind::isConnected(int numOne, int numTwo)
{
	VERIFY_RANGE_ERRORS retValue = UNDEFINED_ERROR;

    retValue = this->p_verifyRange(numOne, numTwo);

    if(NUM_ONE_OUTSIDE_RANGE == retValue)
    {
        throw MyException("ERROR: first value is not within the array range");
    } 
    else if(NUM_TWO_OUTSIDE_RANGE == retValue)
    {
        throw MyException("ERROR: second value is not within the array range");
    }
    else if(UNDEFINED_ERROR == retValue)
    {
        throw MyException("ERROR: unknown problem occured isConnected");
    }
    
    if(VALUES_WITHIN_RANGE == retValue)
    {
        this->p_isConnected(numOne, numTwo);
    }
    else
    {
        throw MyException("ERROR: Something really weird happened");
    }
    
}

void C_unionFind::printArray()
{
	if(NULL == this->p_dataArray)
    {
        throw MyException("WARNING: No array to print");
    }
    else
    {
        this->p_printArray();
    }
}


void C_unionFind::p_initArray(int userArraySize)
{
	if( 0 > userArraySize)
    {
        throw MyException("Error: can't use negative numbers");
    }
    else
    {
        this->p_arraySize = userArraySize;
        this->p_dataArray = new int[this->p_arraySize];
        
        int index = 0;
        for(index = 0; index < this->p_arraySize; ++index)
        {
            this->p_dataArray[index] = index;
        }
    }
}

void C_unionFind::p_unionNumbers(int numOne, int numTwo)
{
	int index = 0;

    for(index = 0; index < this->p_arraySize; ++index)
    {
        if(this->p_dataArray[index] == numOne)
        {
            this->p_dataArray[index] = numTwo;
            //conected INDEX to numTwo.
        }
    }
    

}

bool C_unionFind::p_isConnected(int numOne, int numTwo)
{
	bool connectionVerified = false;
    
    if(this->p_dataArray[numOne] == numTwo)
    {
        connectionVerified = true;
    }

    return connectionVerified;


}

VERIFY_RANGE_ERRORS C_unionFind::p_verifyRange(int numOne, int numTwo)
{
    VERIFY_RANGE_ERRORS retValue = UNDEFINED_ERROR;     

    if(numOne < this->p_arraySize)
    {
        if(numTwo < this->p_arraySize)
        {
            retValue = VALUES_WITHIN_RANGE;
        }
        else
        {
            retValue = NUM_TWO_OUTSIDE_RANGE;
        }
    }
    else
    {
        retValue = NUM_ONE_OUTSIDE_RANGE;
    }
    return retValue;
}

void C_unionFind::p_printArray()
{
    int index = 0;

    for(index = 0; index<this->p_arraySize; ++index)
    {
        cout<<"array["<<index<<"] = "<<this->p_dataArray[index]<<endl;
    }
}