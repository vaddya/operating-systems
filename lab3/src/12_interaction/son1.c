#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int pid = getpid();
    int ppid = getppid();
    printf("son1: PID = %d, PPID = %d\n", pid, ppid);
    printf("son1: Father creates and waits, sleep(3)\n");
    sleep(3);
    return 0;
}