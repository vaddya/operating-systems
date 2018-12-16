#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void (*mysig(int sig, void (*hnd)(int)))(int s) {
    struct sigaction act, oact;
    act.sa_handler = hnd;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;
    if (sigaction(sig, &act, &oact) < 0) {
        return (void *) SIG_ERR;
    }
    return (void *) oact.sa_handler;
}

void handler(int sig) {
    printf("Caught signal %s\n", strsignal(sig));
    sleep(60);
}

int main() {
    mysig(SIGUSR1, handler);
    while (1) {
        pause();
    }
    return 0;
}
