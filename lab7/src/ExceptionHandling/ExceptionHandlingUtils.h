#include <Windows.h>
#include <intrin.h>
#include <excpt.h>
#include <eh.h>
#include <string.h>
#include <iostream>
#include <sstream>

DWORD FilterException(DWORD actual, DWORD expected);

const char* GetExceptionName(unsigned code);

void PrintExceptionInfo(EXCEPTION_RECORD &excRec, CONTEXT &ctx);

// Custom unhandled exception filter
DWORD MyUnhandledExceptionFilter(EXCEPTION_POINTERS* excInfo);

// Custom translator
void MyTranslator(unsigned code, EXCEPTION_POINTERS* excInfo);

// For AbnormalTermination program
enum class Type { OK, EXCEPTION, GOTO, LEAVE };

Type ParseType(const char* str);
