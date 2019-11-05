#include "ExceptionHandlingUtils.h"

int main18()
{
    __try
    {
        __try
        {
            int a = 0;
            cout << 1 / a << endl;
            cout << "After division" << endl;
        }
        __finally
        {
            cout << "Finally" << endl;
        }
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except-finally" << endl;
    return 0;
}
