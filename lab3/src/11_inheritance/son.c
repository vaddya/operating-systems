#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (mlockall((MCL_CURRENT | MCL_FUTURE)) < 0) {
        perror("mlockall");
    }
    int fdrd = atoi(argv[1]);
    int fdwr = atoi(argv[2]);
    int pid = getpid();
    int ppid = getppid();
    printf("%s fdrd = %d, fdwr = %d\n", argv[0], fdrd, fdwr);
    printf("%s params: PID = %d PPID = %d\n", argv[0], pid, ppid);
    sleep(5);
    char c;
    while (1) {
        if (read(fdrd, &c, 1) != 1)
            break;
        write(fdwr, &c, 1);
        printf("%s: %c\n", argv[0], c);
        sched_yield();
    }
    return 0;
}