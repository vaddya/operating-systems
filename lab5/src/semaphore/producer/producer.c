#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "../shm.h"

int main(int argc, char **argv) {
    Message *p_msg;
    char keyFile[BUFFER_SIZE];
    bzero(keyFile, BUFFER_SIZE);
    if (argc < 2) {
        printf("Using default key file %s\n", DEF_KEY_FILE);
        strcpy(keyFile, DEF_KEY_FILE);
    } else {
        strcpy(keyFile, argv[1]);
    }
    key_t key;
    int shmemory;
    int semaphore;
    if ((key = ftok(keyFile, 'Q')) < 0) {
        printf("Can't get key for key file %s and id 'Q'\n", keyFile);
        return 1;
    }
    if ((shmemory = shmget(key, sizeof(Message), 0666)) < 0) {
        perror("Can't create shm");
        return 1;
    }
    if ((p_msg = (Message *) shmat(shmemory, 0, 0)) < 0) {
        perror("Error while attaching shm");
        return 1;
    }
    if ((semaphore = semget(key, 2, 0666)) < 0) {
        perror("Error while creating semaphore");
        return 1;
    }
    char buf[BUFFER_SIZE];
    while (1) {
        bzero(buf, BUFFER_SIZE);
        printf("Type message to server. Empty string to finish:\n");
        fgets(buf, BUFFER_SIZE, stdin);
        if (strlen(buf) == 1 && buf[0] == '\n') {
            printf("bye-bye\n");
            break;
        }
        if (semop(semaphore, writeEna, 1) < 0) {
            perror("Can't execute a operation");
            return 1;
        }
        sprintf(p_msg->buf, "%s", buf);
        if (semop(semaphore, setReadEna, 1) < 0) {
            perror("Can't execute a operation");
            return 1;
        }
    }
    if (shmdt(p_msg) < 0) {
        perror("Error while detaching shm");
        return 1;
    }
    return 0;
}