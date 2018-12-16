#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

pthread_t t1;
pthread_t t2;

void handler(int sig) {
    printf("Caught signal %s\n", strsignal(sig));
    pthread_exit(0);
}

void *thread1() {
    for (int i = 0; i < 2; i++) {
        printf("thread1: [%d] sleep(5)\n", i);
        sleep(5);
        pthread_kill(t2, SIGUSR1);
    }
    printf("thread1: done\n");
}

void *thread2() {
    signal(SIGUSR1, handler);
    for (int n = 0; n < 10; n++) {
        printf("thread2: [%d] sleep(1)\n", n);
        sleep(1);
    }
    printf("thread2: done\n");
}

int main(int argc, char **argv) {
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}