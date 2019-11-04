#include "ExceptionHandlingUtils.h"

using namespace std;

int main23()
{
    EXCEPTION_RECORD excRec;
    CONTEXT ctx;
    __try
    {
        RaiseException(EXCEPTION_ILLEGAL_INSTRUCTION, 0, 0, NULL);
        cout << "After raise" << endl;
    }
    __except (
        excRec = *(GetExceptionInformation())->ExceptionRecord,
        ctx = *(GetExceptionInformation())->ContextRecord,
        FilterException(GetExceptionCode(), EXCEPTION_ILLEGAL_INSTRUCTION))
    {
        cout << hex << "Caught using filter: EXCEPTION_ILLEGAL_INSTRUCTION" << endl
            << "Expetcted exception code=0x" << EXCEPTION_ILLEGAL_INSTRUCTION << endl;
        PrintExceptionInfo(excRec, ctx);
    }
    cout << "After try-except" << endl;
    return 0;
}
