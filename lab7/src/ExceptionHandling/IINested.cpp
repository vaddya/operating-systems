#include "ExceptionHandlingUtils.h"

using namespace std;

int main()
{
    __try
    {
        __try
        {
            __try
            {
                __ud2();
                cout << "After ud" << endl;
            }
            __except (FilterException(GetExceptionCode(), EXCEPTION_INT_OVERFLOW))
            {
                cout << "1: Caught using filter: EXCEPTION_INT_OVERFLOW" << endl;
            }
            cout << "After try-except 1" << endl;
        }
        __except (FilterException(GetExceptionCode(), EXCEPTION_ILLEGAL_INSTRUCTION))
        {
            cout << "2: Caught using filter: EXCEPTION_ILLEGAL_INSTRUCTION" << endl;
            __ud2();
        }
        cout << "After try-except 2" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_ILLEGAL_INSTRUCTION))
    {
        cout << "3: Caught using filter: EXCEPTION_ILLEGAL_INSTRUCTION" << endl;
    }
    cout << "After try-except 3" << endl;
    return 0;
}
