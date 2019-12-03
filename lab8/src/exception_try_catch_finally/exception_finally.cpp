#include "exceptions.h"

int main() {
    try {
        throwException(SIGFPE, "1");
        std::cout << "After exception" << std::endl;
    } catch (const Exception &e) {
        std::cout << "Caught exception: " << e;
    } finally {

    };
    std::cout << "After try-catch" << std::endl;
    throwException(SIGFPE, "2");
    return 0;
}
