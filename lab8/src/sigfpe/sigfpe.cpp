#include <iostream>

int main() {
    std::cout << "Generating SIGFPE" << std::endl;
    int a = 5;
    int b = 0;
    std::cout << a / b << std::endl;
    return 0;
}
