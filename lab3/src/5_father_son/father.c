#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int pid = getpid();
    int ppid = getppid();
    printf("father params: PID = %i, PPID = %i\n", pid, ppid);
    if (fork() == 0) {
        execl("son", "son", NULL);
    }
    system("ps xf > dump.txt");
    int status;
    wait(&status);
    printf("child process is finished with status %d\n", status);
    return 0;
}
