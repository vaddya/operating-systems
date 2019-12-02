#include "utils.h"

void generateSigfpe() {
    std::cout << "Generating SIGFPE" << std::endl;
    int a = 5;
    int b = 0;
    std::cout << a / b << std::endl;
}

void generateSigill() {
    std::cout << "Generating SIGILL" << std::endl;
    __builtin_trap();
}

__sighandler_t signalHandler(int sig, __sighandler_t handler) {
    std::cout << "Setting signal handler: " << toString(sig) << std::endl;
    return signal(sig, handler);
}

__sighandler_t sigactionHandler(int sig, __sighandler_t handler) {
    std::cout << "Setting sigaction handler: " << toString(sig) << std::endl;
    struct sigaction action{}, oldAction{};
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(sig, &action, &oldAction) < 0) {
        return SIG_ERR;
    }
    return oldAction.sa_handler;
}

void printingHandler(int sig) {
    std::cout << "Caught signal: " << toString(sig) << std::endl;
    signal(sig, SIG_DFL);
}

std::string toString(int sig) {
    std::ostringstream out;
    out << sig << " " << strsignal(sig);
    return out.str();
}