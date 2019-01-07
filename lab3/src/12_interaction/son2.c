#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pid = getpid();
    int ppid = getppid();
    char command[50];
    sprintf(command, "ps xjf | grep son2 >> %s", argv[1]);
    printf("son2: PID = %d, PPID = %d\n", pid, ppid);
    printf("son2: Father finished before son termination without waiting for it\n");
    sleep(10);
    ppid = getppid();
    printf("son2: PID = %d, PPID = %d\n", pid, ppid);
    system(command);
    return 0;
}
