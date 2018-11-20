#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>
#include <string.h>

int handling_count;

void handler(int sig) {
    static int i = 0;
    printf("\nhandler: signal \"%s = %d\" is received for %d-th time\n", strsignal(sig), sig, i + 1);
    if (++i == handling_count) {
        printf("handler: setting default handler\n");
        signal(SIGINT, SIG_DFL);
    }
}

void *thread() {
    signal(SIGINT, handler);
    for (int n = 0; n < 10; n++) {
        printf("thread: [%d] sleep(1)\n", n);
        sleep(1);
    }
}

int main(int argc, char **argv) {
    handling_count = argc > 1 ? atoi(argv[1]) : 1;
    pthread_t t;
    pthread_create(&t, NULL, thread, NULL);
    pthread_join(t, NULL);
    return 0;
}