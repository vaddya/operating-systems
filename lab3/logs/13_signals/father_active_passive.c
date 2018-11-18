#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <signal.h>
#include <time.h>

int main(int argc, char **argv) {
    int pid = getpid();
    int ppid = getppid();
    int pid1;
    if ((pid1 = fork()) == 0) {
        execl("son_active", "son_active", NULL);
    }
    int pid2;
    if ((pid2 = fork()) == 0) {
        execl("son_passive", "son_passive", NULL);
    }
    sleep(1);
    for (int i = 0; i < 4; ++i) {
        time_t t = time(0);
        printf("father: [%d] sending SIGINT at %s", i, ctime(&t));
        kill(pid1, SIGINT);
        kill(pid2, SIGINT);
        sleep(1);
    }
    wait(0);
    wait(0);
    return 0;
}