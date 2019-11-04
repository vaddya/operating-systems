#include <iostream>
#include <sstream>
#include <intrin.h>
#include <Windows.h>
#include <excpt.h>
#include <eh.h>

DWORD FilterException(DWORD actual, DWORD expected);

VOID PrintExceptionInfo(EXCEPTION_RECORD &excRec, CONTEXT &ctx);

DWORD MyUnhandledExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo);
