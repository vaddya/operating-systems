#include "exceptions.h"

int main() {
    try {
        std::cout << "Before goto" << std::endl;
        goto lbl;
        throwException(SIGFPE, "1");
        std::cout << "After exception" << std::endl;
    } catch (const Exception &e) {
        std::cout << "Caught exception: " << e;
        throwStdException("2");
    }
    std::cout << "After outer try-catch" << std::endl;
lbl:
    std::cout << "After label" << std::endl;
    return 0;
}
