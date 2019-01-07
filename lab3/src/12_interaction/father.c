#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *save = argc > 1 ? argv[1] : "tree.txt";
    int pid = getpid();
    int ppid = getppid();
    int sid = getsid(pid);
    char command[50];
    sprintf(command, "ps xjf | grep \"STAT\\|%d\" > %s", sid, save);
    printf("father: SID = %d, PID = %d, PPID = %d\n", sid, pid, ppid);
    int pid1;
    if ((pid1 = fork()) == 0) {
        execl("son1", "son1", NULL);
    }
    if (fork() == 0) {
        execl("son2", "son2", save, NULL);
    }
    if (fork() == 0) {
        execl("son3", "son3", NULL);
    }
    system(command);
    waitpid(pid1, 0, WNOHANG);
    return 0;
}