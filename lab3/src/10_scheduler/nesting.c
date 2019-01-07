#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <wait.h>
#include "utils.h"

int main(int argc, char **argv) {
    print_parameters("father");
    set_priority(0, SCHED_RR, 50);
    if (fork() == 0) {
        if (fork() == 0) {
            if (fork() == 0) {
                execl("son", "son3", NULL);
            }
            execl("son", "son2", NULL);
        }
        execl("son", "son1", NULL);
    }
    print_current_priority("father");
    wait(0);
    return 0;
}
