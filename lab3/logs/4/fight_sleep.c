#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>

int main(int argc, char **argv) {
    int m = 5000;
    int n = 1;
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    printf("pid = %i\n", pid);
    if (pid != 0) {
        for (int j = 1; j <= 1000; j++) {
            m -= 1;
            usleep(1);
        }
        printf("parent end: %i\n", m);
    } else {
        for (int i = 1; i <= 1000; i++) {
            n += 1;
            usleep(1);
        }
        printf("child end: %d\n", n);
    }
    return 0;
}
