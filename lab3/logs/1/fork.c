#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>

int main(int argc, char **argv) {
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        printf("new PID = %d, PPID = %d \n", getpid(), getppid());
    } else {
        printf("old PID = %d, PPID = %d \n", getpid(), getppid());
    }
    printf("Process end\n");
    return 0;
}