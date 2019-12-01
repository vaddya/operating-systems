#include <iostream>

int main() {
    std::cout << "Generating SIGILL" << std::endl;
    __builtin_trap();
    return 0;
}
