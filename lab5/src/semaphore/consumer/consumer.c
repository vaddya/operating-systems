#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "../shm.h"

Message *p_msg;
int shmemory;
int semaphore;

void handler(int sig) {
    if (shmdt(p_msg) < 0) {
        perror("Error while detaching shm");
        exit(1);
    }
    if (shmctl(shmemory, IPC_RMID, 0) < 0) {
        perror("Error while deleting shm");
        exit(1);
    }
    if (semctl(semaphore, 0, IPC_RMID) < 0) {
        perror("Error while deleting semaphore");
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
    key_t key;
    if ((key = ftok(keyFile, 'Q')) < 0) {
        printf("Can't get key for key file %s and id 'Q'\n", keyFile);
        return 1;
    }
    if ((shmemory = shmget(key, sizeof(Message), IPC_CREAT | 0666)) < 0) {
        perror("Can't create shm");
        return 1;
    }
    if ((p_msg = (Message *) shmat(shmemory, 0, 0)) < 0) {
        perror("Error while attaching shm");
        return 1;
    }
    signal(SIGINT, handler);
    if ((semaphore = semget(key, 2, IPC_CREAT | 0666)) < 0) {
        perror("Error while creating semaphore");
        kill(getpid(), SIGINT);
    }
    if (semop(semaphore, setWriteEna, 1) < 0) {
        perror("Error semop\n");
        kill(getpid(), SIGINT);
    }
    while (1) {
        if (semop(semaphore, readEna, 1) < 0) {
            printf("execution complete\n");
            kill(getpid(), SIGINT);
        }
        printf("Client's message: %s", p_msg->buf);
        if (semop(semaphore, setWriteEna, 1) < 0) {
            printf("execution complete\n");
            kill(getpid(), SIGINT);
        }
    }
}
