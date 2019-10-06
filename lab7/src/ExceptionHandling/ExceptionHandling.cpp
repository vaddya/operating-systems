#include <iostream>
#include <Windows.h>

#include <excpt.h>
#include <intrin.h>

using namespace std;

LONG FilterException(DWORD actual, DWORD expected)
{
    return actual == expected
        ? EXCEPTION_EXECUTE_HANDLER
        : EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
    __try
    {
        int a = 0;
        int b = 1 / a;
        cout << b << endl;
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << "Caught: EXCEPTION_INT_DIVIDE_BY_ZERO" << endl;
    }

    __try
    {
        __ud2();
    }
    __except (FilterException(GetExceptionCode(), EXCEPTION_ILLEGAL_INSTRUCTION))
    {
        cout << "Caught: EXCEPTION_ILLEGAL_INSTRUCTION" << endl;
    }

    cout << "End" << endl;
}
