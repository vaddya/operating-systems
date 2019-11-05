#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()

using namespace std;

int main29(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Illegal arguments! Use: ok | exception | goto | leave" << endl;
        return 1;
    }
    Type type = ParseType(argv[1]);
    __try
    {
        switch (type)
        {
        case Type::OK:
            cout << "It's OK!" << endl; break;
        case Type::EXCEPTION:
            GENERATE_EXCEPTION; break;
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
