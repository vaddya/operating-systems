#include "exceptions.h"

int main() {
    throwException(SIGFPE, "1");
    return 0;
}
