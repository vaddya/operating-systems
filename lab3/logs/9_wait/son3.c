#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int pid = getpid();
    int ppid = getppid();
    printf("son params: PID = %i, PPID = %i\n", pid, ppid);
    sleep(5);
    exit(-1);
}
