#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
    int pid = getpid();
    for (int i = -100; i < 1; i++) {
        setpriority(PRIO_PROCESS, pid, i);
        int pr = getpriority(PRIO_PROCESS, pid);
        if (pr != i) {
            continue;
        }
        printf("Lower bound = %d\n", pr);
        printf("Asked %d, got %d\n", i, pr);
        break;
    }
    for (int i = 1; i < 100; i++) {
        setpriority(PRIO_PROCESS, pid, i);
        int pr = getpriority(PRIO_PROCESS, pid);
        if (pr == i) {
            continue;
        }
        printf("Upper bound = %d\n", pr);
        printf("Asked %d, got %d\n", i, pr);
        break;
    }
    return 0;
}