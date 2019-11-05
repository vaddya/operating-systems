#include "ExceptionHandlingUtils.h"

int main17()
{
    _set_se_translator(MyTranslator);
    try
    {
        int a = 0;
        cout << 1 / a << endl;
        cout << "After division" << endl;
    }
    catch (const exception &e)
    {
        cout << "Caught using C++ try-catch: " << e.what() << endl;
    }
    cout << "After try-catch" << endl;
    return 0;
}
