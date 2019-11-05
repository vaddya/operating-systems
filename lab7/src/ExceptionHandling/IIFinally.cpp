#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()
#define EXCEPTION_TYPE EXCEPTION_ILLEGAL_INSTRUCTION

using namespace std;

int main28()
{
    __try
    {
        __try
        {
            GENERATE_EXCEPTION;
            cout << "After ud" << endl;
        }
        __finally
        {
            cout << "Finally" << endl;
        }
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_TYPE))
    {
        cout << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except-finally" << endl;
    return 0;
}
