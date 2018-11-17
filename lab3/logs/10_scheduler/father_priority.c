#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <wait.h>
#include "utils.h"

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
    int son1_priority = atoi(argv[2]);
    int son2_priority = atoi(argv[3]);
    int son3_priority = atoi(argv[4]);
    set_priority(0, policy, 50);
    if (fork() == 0) {
        set_priority(0, SCHED_FIFO, son1_priority);
        execl("son_calc", "son1", NULL);
    }
    if (fork() == 0) {
        set_priority(0, policy, son2_priority);
        execl("son_calc", "son2", NULL);
    }
    if (fork() == 0) {
        set_priority(0, policy, son3_priority);
        execl("son_calc", "son3", NULL);
    }
    print_current_priority("father");
    wait(0);
    wait(0);
    wait(0);
    return 0;
}
