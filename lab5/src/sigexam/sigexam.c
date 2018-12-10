#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void handler(int sig) {
    printf("Caught signal %s\n", sig == SIGUSR1 ? "SIGUSR1" : "SIGUSR2");
    printf("Parent = %d\n", getppid());
    signal(sig, SIG_DFL);
}

int main(int argc, char **argv) {
    printf("Father started: PID = %i, PPID = %i\n", getpid(), getppid());
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGINT, SIG_DFL);
    signal(SIGCHLD, SIG_IGN);
    if (fork() == 0) {
        printf("Son started: PID = %i, PPID = %i\n", getpid(), getppid());
        if (kill(getppid(), SIGUSR1) != 0) {
            printf("Error while sending SIGUSR1\n");
            exit(1);
        }
        printf("Successfully sent SIGUSR1\n");
        return 0;
    }
    wait(NULL);
    while (1) {
        pause();
    }
    return 0;
}