#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

const char *DEF_KEY_FILE = "../key";
typedef struct {
    long type;
    char buf[100];
} Message;

int main(int argc, char **argv) {
    char keyFile[100];
    bzero(keyFile, 100);
    if (argc < 2) {
        printf("Using default key file %s\n", DEF_KEY_FILE);
        strcpy(keyFile, DEF_KEY_FILE);
    } else {
        strcpy(keyFile, argv[1]);
    }
    key_t key = ftok(keyFile, 'Q');
    if (key == -1) {
        printf("Got no key for key file %s and id 'Q'\n", keyFile);
        return 1;
    }
    int queue = msgget(key, 0);
    if (queue < 0) {
        printf("Can't create queue\n");
        return 1;
    }
    Message mes;
    ssize_t res;
    while (1) {
        bzero(mes.buf, 100);
        fgets(mes.buf, 100, stdin);
        mes.buf[strlen(mes.buf) - 1] = '\0';
        mes.type = 1L;
        res = msgsnd(queue, (void *) &mes, sizeof(Message), 0);
        if (res != 0) {
            perror("Send msg error");
            return 1;
        }
        res = msgrcv(queue, &mes, sizeof(Message), 2L, 0);
        if (res < 0) {
            perror("Receive msg error");
            return 1;
        }
        printf("Server's response: %s\n", mes.buf);
    }
    return 0;
}