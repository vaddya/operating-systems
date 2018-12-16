#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

const char *CHANNEL1 = "../channel1";
const char *CHANNEL2 = "../channel2";
const int BUFFER_SIZE = 100;

int main() {
    int chan1 = open(CHANNEL1, O_RDONLY);
    if (chan1 == -1) {
        perror("Can't open channel1 for reading");
        return 1;
    }
    int chan2 = open(CHANNEL2, O_WRONLY);
    if (chan2 == -1) {
        perror("Can't open channel2 for reading");
        return 1;
    }
    char fileName[BUFFER_SIZE];
    bzero(fileName, BUFFER_SIZE);
    ssize_t res = read(chan1, fileName, BUFFER_SIZE);
    if (res <= 0) {
        perror("Can't read file name from channel1");
        return 1;
    }
    printf("Read file name: %s\n", fileName);
    FILE *f = fopen(fileName, "r");
    if (!f) {
        perror("Can't open file");
        return 1;
    }
    char buf[100];
    while (!feof(f)) {
        bzero(buf, BUFFER_SIZE);
        res = fread(buf, sizeof(char), BUFFER_SIZE, f);
        write(chan2, buf, res);
        printf("Write: %s\n", buf);
    }
    fclose(f);
    close(chan1);
    close(chan2);
    return 0;
}
