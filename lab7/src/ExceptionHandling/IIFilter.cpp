#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()
#define EXCEPTION_TYPE EXCEPTION_ILLEGAL_INSTRUCTION

int main22()
{
    __try
    {
        GENERATE_EXCEPTION;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_TYPE))
    {
        cout << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
