#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    signal(SIGINT, SIG_IGN);
    int pid = getpid();
    int ppid = getppid();
    printf("%s: PID = %d, PPID = %d\n", argv[0], pid, ppid);
    printf("%s: sleep(3)\n", argv[0]);
    sleep(3);
    printf("%s: done\n", argv[0]);
    return 0;
}