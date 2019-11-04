#include <iostream>
#include <cstring>
#include "ExceptionHandlingUtils.h"

using namespace std;

enum Type { OK, EXCEPTION, GOTO, LEAVE };

Type parseType(const char* str) {
    if (!strcmp(str, "ok"))
        return OK;
    else if (!strcmp(str, "exception"))
        return EXCEPTION;
    else if (!strcmp(str, "goto"))
        return GOTO;
    else if (!strcmp(str, "leave"))
        return LEAVE;
    else
        throw new exception("Unknown type");
}

int main19(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Illegal arguments! Use: ok | exception | goto | leave" << endl;
        return 1;
    }
    Type type = parseType(argv[1]);
    int a = 1, b = 0;
    __try
    {
        switch (type) 
        {
            case OK:
                cout << a << " + " << b << " = " << a + b << endl; break;
            case EXCEPTION:
                cout << a << " / " << b << " = " << a / b << endl; break;
            case GOTO:
                goto lbl; break;
            case LEAVE:
                __leave; break;
        }
    }
    __finally
    {
        cout << "Finally AbnormalTermination=" << AbnormalTermination() << endl;
    }
    cout << "After try-except-finally" << endl;
lbl:
    cout << "After label" << endl;
    return 0;
}
