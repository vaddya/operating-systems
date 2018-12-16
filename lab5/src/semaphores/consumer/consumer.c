#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <strings.h>
#include <string.h>
#include "../shm.h"

int *buf;
int shmemory;
int semaphore;

void handler(int sig) {
    shmdt(buf);
    shmctl(shmemory, IPC_RMID, 0);
    semctl(semaphore, 0, IPC_RMID);
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
    if ((shmemory = shmget(key, (BUF_SIZE + 1) * sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("Can't create shm");
        return 1;
    }
    if ((buf = (int *) shmat(shmemory, 0, 0)) < 0) {
        perror("Error while attaching shm");
        return 1;
    }
    signal(SIGINT, handler);
    if ((semaphore = semget(key, 3, IPC_CREAT | 0666)) < 0) {
        perror("Error while creating semaphore");
        kill(getpid(), SIGINT);
    }
    buf[BUF_SIZE] = -1;
    int j = 0;
    for (j = 0; j < BUF_SIZE; ++j) {
        buf[j] = -1;
    }
    if (semop(semaphore, setFree, 1) < 0) {
        perror("execution complete");
        kill(getpid(), SIGINT);
    }
    if (semop(semaphore, memUnlock, 1) < 0) {
        perror("execution complete");
        kill(getpid(), SIGINT);
    }
    printf("Press enter to start working");
    getchar();
    int i = 0;
    for (i = 0; i < 15; ++i) {
        if (semop(semaphore, waitNotEmpty, 1) < 0) {
            perror("execution complete");
            kill(getpid(), SIGINT);
        }
        if (semop(semaphore, memLock, 1) < 0) {
            perror("execution complete");
            kill(getpid(), SIGINT);
        }
        int res = buf[buf[BUF_SIZE]];
        buf[BUF_SIZE] = buf[BUF_SIZE] - 1;
        printf("Remove %d from cell %d\n", res, buf[BUF_SIZE] + 1);
        if (semop(semaphore, memUnlock, 1) < 0) {
            perror("execution complete");
            kill(getpid(), SIGINT);
        }
        if (semop(semaphore, releaseEmpty, 1) < 0) {
            perror("execution complete");
            kill(getpid(), SIGINT);
        }
    }
    return 0;
}
