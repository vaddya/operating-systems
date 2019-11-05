#include "ExceptionHandlingUtils.h"

using namespace std;

int main14()
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) MyUnhandledExceptionFilter);
    __try
    {
        int a = 0;
        cout << 1 / a << endl;
        cout << "After division" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_OVERFLOW))
    {
        cout << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
