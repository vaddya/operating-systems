#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
    int pid = getpid();
    int pr = getpriority(PRIO_PROCESS, pid);
    printf("PID: %d, priority: %d\n", pid, pr);

    int n = 20;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    for (int i = 0; i < n; ++i) {
        pr = getpriority(PRIO_PROCESS, i);
        if (pr != 0) {
            printf("PID: %d, priority: %d\n", i, pr);
        }
    }
    return 0;
}