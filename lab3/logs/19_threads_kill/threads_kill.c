#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *thread1() {
    int tid = syscall(SYS_gettid);
    char command[10];
    sprintf(command, "kill -9 %d", tid);
    printf("thread1: system(%s)\n", command);
    system(command);
    for (int i = 0; i < 2; i++) {
        printf("thread1: [%d] sleep(5)\n", i);
        sleep(5);
    }
}

void *threadn() {
    for (int n = 0; n < 10; n++) {
        printf("threadn: [%d] sleep(1)\n", n);
        sleep(1);
    }
}

void main() {
    pthread_t t1;
    pthread_t tn;
    system("ps -ALf > dump1");
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&tn, NULL, threadn, NULL);
    system("ps -ALf > dump2_2");
    pthread_join(t1, NULL);
    pthread_join(tn, NULL);
    system("ps -ALf > dump3");
}