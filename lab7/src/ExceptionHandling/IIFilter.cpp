#include "ExceptionHandlingUtils.h"

using namespace std;

int main22()
{
    __try
    {
        __ud2();
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_ILLEGAL_INSTRUCTION))
    {
        cout << "Caught using filter: EXCEPTION_ILLEGAL_INSTRUCTION" << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
