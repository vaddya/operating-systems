#include <stdio.h>
#include <unistd.h>
#include <asm/io.h>
#include <iostream>

#define BASEPORT 0x378

int main() {
    // access port
    if (ioperm(BASEPORT, 1, 1)) {
        std::cout << "Unable to access port" << std::endl;
        return 1;
    }

    // output byte to port
    outb(0, BASEPORT);

    // delay
    usleep(100000);

    // read from port
    byte value = inb(BASEPORT);
    std::cout << "Read from port " << BASEPORT << ": " << value << std::endl;

    return 0;
}
