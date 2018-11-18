#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <signal.h>

int main(int argc, char **argv) {
    int pid = getpid();
    int ppid = getppid();
    int pid1;
    if ((pid1 = fork()) == 0) {
        execl("son1", "son1", NULL);
    }
    int pid2;
    if ((pid2 = fork()) == 0) {
        execl("son2", "son2", NULL);
    }
    int pid3;
    if ((pid3 = fork()) == 0) {
        execl("son3", "son3", NULL);
    }
    sleep(1);
    system("ps -s > signals");
    kill(pid1, SIGINT);
    kill(pid2, SIGINT);
    kill(pid3, SIGINT);
    wait(0);
    wait(0);
    wait(0);
    return 0;
}