#include "exceptions.h"
#include "utils.h"

int main() {
    signalHandler(SIGABRT, printingHandler);
    throwException(SIGFPE, "2");
    return 0;
}
