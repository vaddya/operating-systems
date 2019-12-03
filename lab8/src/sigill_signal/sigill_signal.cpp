#include "utils.h"

int main() {
    signalHandler(SIGILL, printingHandler);
    generateSigill();
    return 0;
}
