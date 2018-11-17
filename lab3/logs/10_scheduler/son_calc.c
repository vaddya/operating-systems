#include <stdio.h>
#include <time.h>
#include "utils.h"

const int MAX_COUNT = 1000000000;

const int TIMESTAMPS = 4;

int main(int argc, char **argv) {
    print_parameters(argv[0]);
    print_current_priority(argv[0]);
    time_t timers[TIMESTAMPS + 1];
    int next_timestamp = 0;
    for (int i = 0; i <= MAX_COUNT; ++i) {
        if (i % (MAX_COUNT / TIMESTAMPS) == 0) {
            timers[next_timestamp++] = time(0);
        }
    }
    for (int j = 0; j < TIMESTAMPS + 1; ++j) {
        printf("%s: [%d] %s", argv[0], j, ctime(&timers[j]));
    }
    printf("%s: done\n", argv[0]);
    return 0;
}
