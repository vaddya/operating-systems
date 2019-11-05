#include "ExceptionHandlingUtils.h"

using namespace std;

int main12()
{
    __try
    {
        int a = 0;
        cout << 1 / a << endl;
        cout << "After division" << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
