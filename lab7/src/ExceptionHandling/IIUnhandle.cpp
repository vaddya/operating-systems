#include "ExceptionHandlingUtils.h"

using namespace std;

int main24()
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)MyUnhandledExceptionFilter);
    __try
    {
        __ud2();
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_OVERFLOW))
    {
        cout << "Caught using filter: EXCEPTION_INT_OVERFLOW" << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
