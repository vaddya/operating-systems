#include "ExceptionHandlingUtils.h"

#define EXCEPTION_TYPE EXCEPTION_ILLEGAL_INSTRUCTION

using namespace std;

int main23()
{
    EXCEPTION_RECORD excRec;
    CONTEXT ctx;
    __try
    {
        RaiseException(EXCEPTION_TYPE, 0, 0, NULL);
        cout << "After raise" << endl;
    }
    __except (
        excRec = *(GetExceptionInformation())->ExceptionRecord,
        ctx = *(GetExceptionInformation())->ContextRecord,
        FilterException(GetExceptionCode(), EXCEPTION_TYPE))
    {
        cout << hex << "Caught using filter: " << GetExceptionName(GetExceptionCode()) << endl
            << "Expetcted exception code=0x" << EXCEPTION_TYPE << endl;
        PrintExceptionInfo(excRec, ctx);
    }
    cout << "After try-except" << endl;
    return 0;
}
