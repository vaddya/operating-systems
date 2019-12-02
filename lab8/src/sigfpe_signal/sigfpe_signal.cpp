#include "utils.h"

int main() {
    signalHandler(SIGFPE, printingHandler);
    generateSigfpe();
    return 0;
}
