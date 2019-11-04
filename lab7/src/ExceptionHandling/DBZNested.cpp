#include "ExceptionHandlingUtils.h"

using namespace std;

int main15()
{
    __try
    {
        __try
        {
            int a = 0;
            __try
            {
                cout << 1 / a << endl;
                cout << "After division" << endl;
            }
            __except (FilterException(GetExceptionCode(), EXCEPTION_INT_OVERFLOW))
            {
                cout << "1: Caught using filter: EXCEPTION_INT_OVERFLOW" << endl;
            }
            cout << "After try-except 1" << endl;
        }
        __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
        {
            cout << "2: Caught using filter: EXCEPTION_INT_DIVIDE_BY_ZERO" << endl;
            int b = 0;
            cout << 2 / b << endl;
        }
        cout << "After try-except 2" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << "3: Caught using filter: EXCEPTION_INT_DIVIDE_BY_ZERO" << endl;
    }
    cout << "After try-except 3" << endl;
    return 0;
}
