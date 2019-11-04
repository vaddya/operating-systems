#include <iostream>
#include "ExceptionHandlingUtils.h"

using namespace std;

int main21()
{
    __try
    {
        __ud2();
    }
    __except (GetExceptionCode() == EXCEPTION_ILLEGAL_INSTRUCTION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {
        cout << "Caught using WinAPI: EXCEPTION_ILLEGAL_INSTRUCTION" << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
