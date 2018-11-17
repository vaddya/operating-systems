#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <wait.h>
#include "utils.h"

int main(int argc, char **argv) {
    print_parameters(argv[0]);
    set_priority(0, SCHED_RR, 50);
    if (fork() == 0) {
        execl("son", "son1", NULL);
    }
    if (fork() == 0) {
        execl("son", "son2", NULL);
    }
    print_current_priority(argv[0]);
    wait(0);
    wait(0);
    return 0;
}
