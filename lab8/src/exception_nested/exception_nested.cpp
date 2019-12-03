#include "exceptions.h"

int main() {
    try {
        try {
            try {
                throwException(SIGFPE, "1");
                std::cout << "After exception" << std::endl;
            } catch (int) {
                std::cout << "Wrong handler" << std::endl;
            }
            std::cout << "After inner try-catch" << std::endl;
        } catch (const Exception &e) {
            std::cout << "Caught exception: " << e;
            throwStdException("2");
        }
        std::cout << "After middle try-catch" << std::endl;
    } catch (const std::runtime_error &e) {
        std::cout << "Caught std::runtime_error " << e.what() << std::endl;
    }
    std::cout << "After outer try-catch" << std::endl;
    return 0;
}
