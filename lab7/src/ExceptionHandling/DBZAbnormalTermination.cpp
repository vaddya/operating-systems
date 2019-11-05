#include "ExceptionHandlingUtils.h"

int main19(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Illegal arguments! Use: ok | exception | goto | leave" << endl;
        return 1;
    }
    Type type = ParseType(argv[1]);
    int a = 1, b = 0;
    __try
    {
        switch (type) 
        {
        case Type::OK:
            cout << a << " + " << b << " = " << a + b << endl; break;
        case Type::EXCEPTION:
            cout << a << " / " << b << " = " << a / b << endl; break;
        case Type::GOTO:
            goto lbl; break;
        case Type::LEAVE:
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
