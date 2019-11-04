#include "ExceptionHandlingUtils.h"

using namespace std;

DWORD FilterException(DWORD actual, DWORD expected)
{
    return actual == expected
        ? EXCEPTION_EXECUTE_HANDLER
        : EXCEPTION_CONTINUE_SEARCH;
}

VOID PrintExceptionInfo(EXCEPTION_RECORD &excRec, CONTEXT &ctx)
{
    cout << hex << "Exception information:" << endl
        << "ExceptionCode=0x" << excRec.ExceptionCode << endl
        << "NumberParameters=0x" << excRec.NumberParameters << endl
        << "ExceptionFlags=0x" << excRec.ExceptionFlags << endl
        << "ContextFlags=0x" << ctx.ContextFlags << endl;
}

DWORD MyUnhandledExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo) {
    cout << hex << "Unhandled exception filter" << endl
        << "ExcpetionCode=0x" << ExceptionInfo->ExceptionRecord->ExceptionCode << endl;
    return EXCEPTION_EXECUTE_HANDLER;
}
