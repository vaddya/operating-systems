#include "ExceptionHandlingUtils.h"

#define GENERATE_EXCEPTION __ud2()

using namespace std;

int main27()
{
    _set_se_translator(MyTranslator);
    try
    {
        GENERATE_EXCEPTION;
    }
    catch (const exception & e)
    {
        cout << "Caught using C++ try-catch: " << e.what() << endl;
    }
    cout << "After try-catch" << endl;
    return 0;
}
