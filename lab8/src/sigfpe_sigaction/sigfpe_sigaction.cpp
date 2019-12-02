#include "utils.h"

int main() {
    sigactionHandler(SIGFPE, printingHandler);
    generateSigfpe();
    return 0;
}
