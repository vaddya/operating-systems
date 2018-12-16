#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

const char *DEF_FILENAME = "../test.txt";
const char *CHANNEL1 = "../channel1";
const char *CHANNEL2 = "../channel2";
const int BUFFER_SIZE = 100;

int main(int argc, char **argv) {
    char fileName[30];
    if (argc < 2) {
        printf("Using default file name %s\n", DEF_FILENAME);
        strcpy(fileName, DEF_FILENAME);
    } else {
        strcpy(fileName, argv[1]);
    }
    ssize_t res = mknod(CHANNEL1, S_IFIFO | 0666, 0);
    if (res) {
        perror("Can't create first channel");
        return 1;
    }
    res = mknod(CHANNEL2, S_IFIFO | 0666, 0);
    if (res) {
        perror("Can't create second channel\n");
        return 1;
    }
    int chan1 = open(CHANNEL1, O_WRONLY);
    if (chan1 == -1) {
        perror("Can't open chan1 for writing\n");
        return 1;
    }
    int chan2 = open(CHANNEL2, O_RDONLY);
    if (chan2 == -1) {
        perror("Can't open chan2 for reading\n");
        return 1;
    }
    write(chan1, fileName, strlen(fileName));
    char buf[BUFFER_SIZE];
    while (1) {
        bzero(buf, BUFFER_SIZE);
        res = read(chan2, buf, BUFFER_SIZE);
        if (res <= 0) {
            break;
        }
        printf("Read: %s\n", buf);
    }
    close(chan1);
    close(chan2);
    unlink(CHANNEL1);
    unlink(CHANNEL2);
    return 0;
}