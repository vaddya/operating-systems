#include <iostream>
#include <sys/io.h>

#define BASEPORT 0x378

int main() {
    // access port
    if (ioperm(BASEPORT, 1, 1)) {
        std::cout << "Unable to access port" << std::endl;
        return 1;
    }

    // output byte to port
    outb(0, BASEPORT);

    // read from port
    unsigned char value = inb(BASEPORT);
    std::cout << "Read from port " << BASEPORT << ": "
        << value << " (" << (int) value << ")" << std::endl;

    return 0;
}
