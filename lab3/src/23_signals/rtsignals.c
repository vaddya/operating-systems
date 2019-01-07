#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>
#include <string.h>

void handler(int sig) {
    printf("handler: signal \"%s = %d\" is received\n", strsignal(sig), sig);
}

void *thread() {
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

int main(int argc, char **argv) {
    pthread_t t;
    pthread_create(&t, NULL, thread, NULL);
    sleep(1);
    pthread_kill(t, SIGUSR1);
    pthread_kill(t, SIGUSR2);
    pthread_kill(t, SIGUSR1);
    pthread_kill(t, SIGRTMIN + 2);
    pthread_kill(t, SIGRTMIN);
    pthread_kill(t, SIGRTMIN + 1);
    pthread_kill(t, SIGRTMIN + 1);
    pthread_kill(t, SIGRTMAX);
    sleep(1);
    pthread_kill(t, SIGKILL);
    return 0;
}