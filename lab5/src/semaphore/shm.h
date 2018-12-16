#ifndef SHM_H
#define SHM_H

const char *DEF_KEY_FILE = "../key";
const int BUFFER_SIZE = 100;

typedef struct {
    long type;
    char buf[100];
} Message;

static struct sembuf readEna[1] = {0, -1, 0};
static struct sembuf writeEna[1] = {1, -1, 0};
static struct sembuf setReadEna[1] = {0, 1, 0};
static struct sembuf setWriteEna[1] = {1, 1, 0};

#endif//SHM_H