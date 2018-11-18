#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

void handler() {
    static int i = 0;
    time_t t = time(0);
    printf("son_active: [%d] ^C - signal received at %s", i, ctime(&t));
    if (++i == 3) {
        signal(SIGINT, SIG_DFL);
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handler);
    int pid = getpid();
    int ppid = getppid();
    printf("%s: PID = %d, PPID = %d\n", argv[0], pid, ppid);
    printf("%s: while(1)\n", argv[0]);
    while (1);
    printf("%s: done\n", argv[0]);
    return 0;
}