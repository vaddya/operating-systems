#include "ExceptionHandlingUtils.h"

DWORD FilterException(DWORD actual, DWORD expected)
{
    return actual == expected
        ? EXCEPTION_EXECUTE_HANDLER
        : EXCEPTION_CONTINUE_SEARCH;
}

const char* GetExceptionName(unsigned code) {
    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
    case EXCEPTION_BREAKPOINT:               return "EXCEPTION_BREAKPOINT";
    case EXCEPTION_DATATYPE_MISALIGNMENT:    return "EXCEPTION_DATATYPE_MISALIGNMENT";
    case EXCEPTION_FLT_DENORMAL_OPERAND:     return "EXCEPTION_FLT_DENORMAL_OPERAND";
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
    case EXCEPTION_FLT_INEXACT_RESULT:       return "EXCEPTION_FLT_INEXACT_RESULT";
    case EXCEPTION_FLT_INVALID_OPERATION:    return "EXCEPTION_FLT_INVALID_OPERATION";
    case EXCEPTION_FLT_OVERFLOW:             return "EXCEPTION_FLT_OVERFLOW";
    case EXCEPTION_FLT_STACK_CHECK:          return "EXCEPTION_FLT_STACK_CHECK";
    case EXCEPTION_FLT_UNDERFLOW:            return "EXCEPTION_FLT_UNDERFLOW";
    case EXCEPTION_ILLEGAL_INSTRUCTION:      return "EXCEPTION_ILLEGAL_INSTRUCTION";
    case EXCEPTION_IN_PAGE_ERROR:            return "EXCEPTION_IN_PAGE_ERROR";
    case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "EXCEPTION_INT_DIVIDE_BY_ZERO";
    case EXCEPTION_INT_OVERFLOW:             return "EXCEPTION_INT_OVERFLOW";
    case EXCEPTION_INVALID_DISPOSITION:      return "EXCEPTION_INVALID_DISPOSITION";
    case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
    case EXCEPTION_PRIV_INSTRUCTION:         return "EXCEPTION_PRIV_INSTRUCTION";
    case EXCEPTION_SINGLE_STEP:              return "EXCEPTION_SINGLE_STEP";
    case EXCEPTION_STACK_OVERFLOW:           return "EXCEPTION_STACK_OVERFLOW";
    default:                                 return "UNKNOWN EXCEPTION";
    }
}

void PrintExceptionInfo(EXCEPTION_RECORD &excRec, CONTEXT &ctx)
{
    cout << hex << "Exception information:" << endl
        << "ExceptionCode=0x" << excRec.ExceptionCode << endl
        << "NumberParameters=0x" << excRec.NumberParameters << endl
        << "ExceptionFlags=0x" << excRec.ExceptionFlags << endl
        << "ContextFlags=0x" << ctx.ContextFlags << endl;
}

DWORD MyUnhandledExceptionFilter(EXCEPTION_POINTERS* excInfo) {
    cout << hex << "Unhandled exception filter" << endl
        << "ExcpetionCode=0x" << excInfo->ExceptionRecord->ExceptionCode << endl;
    return EXCEPTION_EXECUTE_HANDLER;
}

void MyTranslator(unsigned code, EXCEPTION_POINTERS* excInfo) {
    cout << "Translator" << endl;
    ostringstream ss;
    ss << "Exception code=0x" << hex << code;
    throw exception(ss.str().c_str());
}

Type ParseType(const char* str) {
    if (!strcmp(str, "exception"))
        return Type::EXCEPTION;
    else if (!strcmp(str, "goto"))
        return Type::GOTO;
    else if (!strcmp(str, "leave"))
        return Type::LEAVE;
    else
        return Type::OK;
}
