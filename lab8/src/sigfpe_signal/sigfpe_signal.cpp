#include <iostream>
#include <csignal>

void handler(int sig) {
    std::cout << "Caught signal: " << sig << std::endl;
    signal(sig, SIG_DFL);
}

int main() {
    std::cout << "Setting handler for SIGFPE" << std::endl;
    signal(SIGFPE, handler);

    std::cout << "Generating SIGFPE" << std::endl;
    int a = 5;
    int b = 0;
    std::cout << a / b << std::endl;
    return 0;
}
