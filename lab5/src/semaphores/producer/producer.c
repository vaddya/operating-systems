#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <strings.h>
#include <string.h>
#include "../shm.h"

int main(int argc, char **argv) {
    char keyFile[BUFFER_SIZE];
    bzero(keyFile, BUFFER_SIZE);
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
    int shmemory;
    if ((shmemory = shmget(key, (BUF_SIZE + 1) * sizeof(int), 0666)) < 0) {
        perror("Can't create shm");
        return 1;
    }
    int *buf;
    if ((buf = (int *) shmat(shmemory, 0, 0)) < 0) {
        perror("Error while attaching shm");
        return 1;
    }
    int semaphore;
    if ((semaphore = semget(key, 2, 0666)) < 0) {
        perror("Error while creating semaphore");
        return 1;
    }
    printf("Press enter to start working\n");
    getchar();
    int send = 0;
    for (int i = 0; i < 10; i++) {
        if (semop(semaphore, waitNotFull, 1) < 0) {
            perror("Can't execute a operation");
            return 1;
        }
        if (semop(semaphore, memLock, 1) < 0) {
            perror("Can't execute a operation");
            return 1;
        }
        printf("Add %d to cell %d\n", send, buf[BUF_SIZE] + 1);
        ++buf[BUF_SIZE];
        buf[buf[BUF_SIZE]] = send++;
        if (semop(semaphore, memUnlock, 1) < 0) {
            perror("Can't execute a operation");
            return 1;
        }
        if (semop(semaphore, releaseFull, 1) < 0) {
            perror("Can't execute a operation");
            return 1;
        }
    }
    shmdt(buf);
    return 0;
}
