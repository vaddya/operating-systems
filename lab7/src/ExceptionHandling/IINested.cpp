#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()
#define EXCEPTION_TYPE EXCEPTION_ILLEGAL_INSTRUCTION

int main25()
{
    __try
    {
        __try
        {
            __try
            {
                GENERATE_EXCEPTION;
                cout << "After ud" << endl;
            }
            __except (FilterException(GetExceptionCode(), EXCEPTION_INT_OVERFLOW))
            {
                cout << "1: Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
            }
            cout << "After try-except 1" << endl;
        }
        __except (FilterException(GetExceptionCode(), EXCEPTION_TYPE))
        {
            cout << "2: Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
            GENERATE_EXCEPTION;
        }
        cout << "After try-except 2" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_TYPE))
    {
        cout << "3: Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except 3" << endl;
    return 0;
}
