#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEVICE "/dev/chardev"
#define SIZE 128

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: ./app STRING_TO_WRITE\n");
        return -1;
    }

    printf("Opening device: %s\n", DEVICE);
    int fd = open(DEVICE, O_RDWR);
    if (fd == -1) {
        printf("Opening failed\n");
        return -1;
    }
    printf("Device was opened\n");

    printf("Writing to device\n");
    int bytes = write(fd, argv[1], strlen(argv[1]));
    if (bytes <= 0) {
        printf("Writing failed\n");
        return -1;
    }

    char buffer[SIZE];
    bytes = read(fd, buffer, sizeof(buffer));
    if (bytes < 0) {
        printf("Reading failed\n");
        return -1;
    }

    printf("Read %d bytes\n", bytes);
    for (int i = 0; i < bytes; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    printf("Closing device\n");
    close(fd);

    return 0;
}
