#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <zconf.h>
#include <strings.h>
#include <string.h>

const char *DEF_KEY_FILE = "../key";
typedef struct {
    long type;
    char buf[100];
} Message;
int queue;

void handler(int sig) {
    signal(sig, SIG_DFL);
    if (msgctl(queue, IPC_RMID, 0) < 0) {
        printf("Can't delete queue\n");
        exit(1);
    }
}

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
        printf("Got no key for the key file %s and id 'Q'\n", keyFile);
        return 1;
    }
    queue = msgget(key, IPC_CREAT | 0666);
    if (queue < 0) {
        perror("Can't create queue");
        return 1;
    }
    signal(SIGINT, handler);
    Message mes;
    int res;
    while (1) {
        bzero(mes.buf, 100);
        res = msgrcv(queue, &mes, sizeof(Message), 1L, 0);
        if (res < 0) {
            printf("Receive msg error\n");
            kill(getpid(), SIGINT);
        }
        printf("Client's request: %s\n", mes.buf);
        mes.type = 2L;
        bzero(mes.buf, 100);
        strcpy(mes.buf, "OK");
        res = msgsnd(queue, (void *) &mes, sizeof(Message), 0);
        if (res != 0) {
            perror("Send msg error");
            kill(getpid(), SIGINT);
        }
    }
    return 0;
}