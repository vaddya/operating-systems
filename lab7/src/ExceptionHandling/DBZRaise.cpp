#include "ExceptionHandlingUtils.h"

int main13()
{
    EXCEPTION_RECORD excRec;
    CONTEXT ctx;
    __try
    {
        RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
        cout << "After raise" << endl;
    }
    __except (
        excRec = *(GetExceptionInformation())->ExceptionRecord,
        ctx = *(GetExceptionInformation())->ContextRecord,
        FilterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
    {
        cout << hex << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl
            << "Expetcted exception code=0x" << EXCEPTION_INT_DIVIDE_BY_ZERO << endl;
        PrintExceptionInfo(excRec, ctx);
    }
    cout << "After try-except" << endl;
    return 0;
}
