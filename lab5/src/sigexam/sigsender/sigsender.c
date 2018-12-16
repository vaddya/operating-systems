#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: sigsender <pid> <singal>");
        return 1;
    }
    int pid = atoi(argv[1]);
    int signal = atoi(argv[2]);
    printf("Sending signal %s to process %d\n", strsignal(signal), pid);
    if (kill(pid, signal) != 0) {
        perror("Error while sending signal");
        return 1;
    }
    return 0;
}