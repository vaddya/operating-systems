#include "ExceptionHandlingUtils.h"

using namespace std;

int main11()
{
    __try
    {
        int a = 0;
        cout << 1 / a << endl;
        cout << "After division" << endl;
    } 
    __except (GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {
        cout << "Caught using WinAPI: " << GetExceptionName(GetExceptionCode()) << endl;
    }
    cout << "After try-except" << endl;
    return 0;
}
