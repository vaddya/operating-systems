#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

const int BUFFER_SIZE = sizeof(int) + 1;

void set_priority(int pid, int policy, int priority) {
    struct sched_param sp;
    sp.sched_priority = priority;
    if (sched_setscheduler(pid, policy, &sp) == -1) {
        perror("SCHED_SETSCHEDULER");
    }
}

void itoa(int i, char *buffer) {
    sprintf(buffer, "%d", i);
}

int main(int argc, char **argv) {
    if (mlockall((MCL_CURRENT | MCL_FUTURE)) < 0) {
        perror("mlockall");
    }
    set_priority(0, SCHED_RR, 50);

    int fdrd;
    if ((fdrd = open("input.txt", O_RDONLY)) == -1) {
        perror("Opening file");
    }
    char str1[BUFFER_SIZE];
    itoa(fdrd, str1);

    int fdwr;
    if ((fdwr = creat("output.txt", 0666)) == -1) {
        perror("Creating file");
    }
    char str2[BUFFER_SIZE];
    itoa(fdwr, str2);

    if (fork() == 0) {
        set_priority(0, SCHED_RR, 10);
        execl("son", "son1", str1, str2, NULL);
    }
    if (fork() == 0) {
        set_priority(0, SCHED_RR, 10);
        execl("son", "son2", str1, str2, NULL);
    }

    if (close(fdrd) != 0 || close(fdwr) != 0) {
        perror("Closing files");
    }
    wait(0);
    wait(0);
    return 0;
}
