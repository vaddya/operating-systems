#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/chardev"
#define SIZE 32

int main() {
    printf("Opening device: %s\n", DEVICE);
    int fd = open(DEVICE, O_RDWR);
    if (fd == -1) {
        printf("Opening failed\n");
        return -1;
    }
    printf("Device was opened\n");

    char buffer[SIZE];
    int bytes = read(fd, buffer, sizeof(buffer));
    if (bytes < 0) {
        printf("Reading failed\n");
        return -1;
    }

    printf("Read %d bytes\n", bytes);
    for (int i = 0; i < bytes; i++) {
        printf("%c", buffer[i]);
    }

    printf("Closing device\n");
    close(fd);

    return 0;
}
