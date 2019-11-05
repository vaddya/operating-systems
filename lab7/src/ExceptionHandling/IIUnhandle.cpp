#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()

int main24()
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)MyUnhandledExceptionFilter);
    __try
    {
        GENERATE_EXCEPTION;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_OVERFLOW))
    {
        cout << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
