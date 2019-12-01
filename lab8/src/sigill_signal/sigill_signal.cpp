#include <iostream>
#include <csignal>

void handler(int sig) {
    std::cout << "Caught signal: " << sig << std::endl;
    signal(sig, SIG_DFL);
}

int main() {
    std::cout << "Setting handler for SIGILL" << std::endl;
    signal(SIGILL, handler);

    std::cout << "Generating SIGILL" << std::endl;
    __builtin_trap();
    return 0;
}
