#include "ExceptionHandlingUtils.h"

int main16()
{
    __try
    {
        goto lbl;
        int a = 0;
        cout << 1 / a << endl;
        cout << "After division" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << "1 Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except 1" << endl;
lbl:
    cout << "After label" << endl;

    __try
    {
        __leave;
        int a = 0;
        cout << 1 / a << endl;
        cout << "After division" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << "2 Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except 2" << endl;

    return 0;
}
