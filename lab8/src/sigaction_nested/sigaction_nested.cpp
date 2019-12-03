#include "utils.h"

void sigillHandler(int sig) {
    std::cout << "Caught " << toString(sig) << std::endl;
    raise(SIGFPE);
}

void sigfpeHandler(int sig) {
    std::cout << "Caught " << toString(sig) << std::endl;
}

int main() {
    sigactionHandler(SIGILL, sigillHandler);
    sigactionHandler(SIGFPE, sigfpeHandler);
    raise(SIGILL);
    return 0;
}
