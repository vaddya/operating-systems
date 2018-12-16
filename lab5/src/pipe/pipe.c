#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

const char *DEF_FROM = "from.txt";
const char *DEF_TO = "to.txt";
const int BUFFER_SIZE = 100;

int main(int argc, char **argv) {
    char fileToRead[32];
    char fileToWrite[32];
    if (argc < 3) {
        printf("father: using default fileNames '%s','%s'\n", DEF_FROM, DEF_TO);
        strcpy(fileToRead, DEF_FROM);
        strcpy(fileToWrite, DEF_TO);
    } else {
        strcpy(fileToRead, argv[1]);
        strcpy(fileToWrite, argv[2]);
    }
    int fds[2];
    if (pipe(fds) < 0) {
        printf("father: can't create pipe\n");
        exit(1);
    }
    printf("father: pipe is successfully created\n");
    if (fork() == 0) {
        close(fds[0]);
        FILE *fd = fopen(fileToRead, "r");
        if (!fd) {
            printf("son: cant open file %s\n", fileToRead);
            exit(1);
        }
        char buf[BUFFER_SIZE];
        size_t res;
        while (!feof(fd)) {
            bzero(buf, BUFFER_SIZE);
            res = fread(buf, sizeof(char), BUFFER_SIZE, fd);
            printf("son: writing to pipe: %s\n", buf);
            write(fds[1], buf, res);
        }
        fclose(fd);
        close(fds[1]);
        return 0;
    }
    close(fds[1]);
    FILE *f = fopen(fileToWrite, "w");
    if (!f) {
        printf("father: cant open file %s\n", fileToWrite);
        exit(1);
    }
    char buf[BUFFER_SIZE];
    size_t res;
    while (1) {
        bzero(buf, BUFFER_SIZE);
        res = read(fds[0], buf, BUFFER_SIZE);
        if (!res) {
            break;
        }
        printf("father: read from pipe: %s\n", buf);
        fwrite(buf, sizeof(char), res, f);
    }
    fclose(f);
    close(fds[0]);
    return 0;
}