#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>
#include <string.h>

void handler(int sig) {
    static int i = 0;
    int tid = syscall(SYS_gettid);
    printf("\nhandler (tid = %d): signal \"%s = %d\" is received\n", tid, strsignal(sig), sig);
    pthread_exit(NULL);
}

void *thread1() {
    signal(SIGINT, handler);
    int tid = syscall(SYS_gettid);
    for (int n = 0; n < 10; n++) {
        printf("thread1 (tid = %d): [%d] sleep(1)\n", tid, n);
        sleep(1);
    }
}

void *threadn() {
    int tid = syscall(SYS_gettid);
    for (int n = 0; n < 10; n++) {
        printf("threadn (tid = %d): [%d] sleep(1)\n", tid, n);
        sleep(1);
    }
}

int main(int argc, char **argv) {
    pthread_t t1;
    pthread_t tn;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&tn, NULL, threadn, NULL);
    int tid = syscall(SYS_gettid);
    for (int n = 0; n < 10; n++) {
        printf("main (tid = %d): [%d] sleep(1)\n", tid, n);
        sleep(1);
    }
    pthread_join(t1, NULL);
    pthread_join(tn, NULL);
    return 0;
}