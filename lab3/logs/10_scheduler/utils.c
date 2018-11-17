#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include "utils.h"

void print_parameters(char *id) {
    printf("%s: PID = %d, PPID = %d\n", id, getpid(), getppid());
}

void print_current_priority(char *id) {
    char *policy = NULL;
    switch (sched_getscheduler(0)) {
        case SCHED_FIFO:
            policy = "SCHED_FIFO";
            break;
        case SCHED_RR:
            policy = "SCHED_RR";
            break;
        case SCHED_OTHER:
            policy = "SCHED_OTHER";
            break;
        case -1:
            perror("SCHED_GETSCHEDULER");
            break;
    }
    struct sched_param sp;
    if (sched_getparam(0, &sp) != 0) {
        perror("SCHED_GETPARAM");
    }
    printf("%s: %s [%d]\n", id, policy, sp.sched_priority);
}

void set_priority(int pid, int policy, int priority) {
    struct sched_param sp;
    sp.sched_priority = priority;
    if (sched_setscheduler(pid, policy, &sp) == -1) {
        perror("SCHED_SETSCHEDULER");
    }
}