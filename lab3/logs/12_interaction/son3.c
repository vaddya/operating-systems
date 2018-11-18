#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pid = getpid();
    int ppid = getppid();
    printf("son3: PID = %d, PPID = %d\n", pid, ppid);
    printf("son3: terminated zombie\n");
    ppid = getppid();
    printf("son3: PID = %d, PPID = %d\n", pid, ppid);
    return 0;
}