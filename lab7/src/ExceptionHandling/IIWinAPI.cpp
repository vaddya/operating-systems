#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()
#define EXCEPTION_TYPE EXCEPTION_ILLEGAL_INSTRUCTION

using namespace std;

int main21()
{
    __try
    {
        GENERATE_EXCEPTION;
    }
    __except (GetExceptionCode() == EXCEPTION_TYPE ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {
        cout << "Caught using WinAPI: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
