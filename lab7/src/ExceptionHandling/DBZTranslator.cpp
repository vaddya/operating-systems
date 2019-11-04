#include "ExceptionHandlingUtils.h"

using namespace std;

void MyTranslator(unsigned code, EXCEPTION_POINTERS* exc_ptrs) {
    cout << "Translator" << endl;
    ostringstream ss;
    ss << "Exception code=0x" << hex << code;
    throw exception(ss.str().c_str());
}

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
