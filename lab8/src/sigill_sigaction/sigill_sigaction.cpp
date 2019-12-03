#include "utils.h"

int main() {
    sigactionHandler(SIGILL, printingHandler);
    generateSigill();
    return 0;
}
