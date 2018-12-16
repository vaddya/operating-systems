#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <bits/types/siginfo_t.h>

pthread_t t1;
pthread_t t2;

void handler(int sig) {
    printf("handler: signal \"%s = %d\" is received\n", strsignal(sig), sig);
}

void *thread1() {
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGRTMIN, handler);
    signal(SIGRTMIN + 1, handler);
    signal(SIGRTMIN + 2, handler);
    signal(SIGRTMAX, handler);
    signal(SIGKILL, handler);
    for (int n = 0; n < 5; n++) {
        printf("thread: [%d] sleep(1)\n", n);
        sleep(1);
    }
}

void *thread2() {
    sleep(1);
    pthread_kill(t1, SIGUSR1);
    pthread_kill(t1, SIGUSR2);
    pthread_kill(t1, SIGUSR1);
    pthread_kill(t1, SIGRTMIN + 2);
    pthread_kill(t1, SIGRTMIN);
    pthread_kill(t1, SIGRTMIN + 1);
    pthread_kill(t1, SIGRTMIN + 1);
    pthread_kill(t1, SIGRTMAX);
    sleep(1);
    pthread_kill(t1, SIGKILL);
}

int main(int argc, char **argv) {
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}