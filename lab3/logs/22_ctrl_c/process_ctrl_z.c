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
        signal(SIGTSTP, SIG_DFL);
    }
}

int main(int argc, char **argv) {
    handling_count = argc > 1 ? atoi(argv[1]) : 1;
    signal(SIGTSTP, handler);
    for (int n = 0; n < 10; n++) {
        printf("main: [%d] sleep(1)\n", n);
        sleep(1);
    }
    return 0;
}