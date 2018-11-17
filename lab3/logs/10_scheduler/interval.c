#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <wait.h>
#include <string.h>
#include "utils.h"

void print_sched_interval(char *id) {
    struct timespec ts;
    if (sched_rr_get_interval(0, &ts) == 0) {
        double sec = ts.tv_sec + ts.tv_nsec / 1000000000.0;
        printf("%s: interval %g sec\n", id, sec);
    } else {
        perror("SCHED_RR_GET_INTERVAL");
    }
}

int main(int argc, char **argv) {
    print_parameters("father");
    int policy;
    if (strcmp(argv[1], "RR") == 0) {
        policy = SCHED_RR;
    } else if (strcmp(argv[1], "FIFO") == 0) {
        policy = SCHED_FIFO;
    } else {
        policy = SCHED_OTHER;
    }
    set_priority(0, policy, 50);
    print_sched_interval("father");
    if (fork() == 0) {
        print_sched_interval("son");
        execl("son", "son", NULL);
    }
    wait(0);
    return 0;
}