#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "utils.h"

const int MAX_COUNT = 1000000000;

const int TIMESTAMPS = 4;

void *thread1() {
    set_thread_priority(SCHED_RR, 50);
    print_current_thread_priority("thread1");
    time_t timers[TIMESTAMPS + 1];
    int next_timestamp = 0;
    for (int i = 0; i <= MAX_COUNT; ++i) {
        if (i % (MAX_COUNT / TIMESTAMPS) == 0) {
            timers[next_timestamp++] = time(0);
        }
    }
    for (int j = 0; j < TIMESTAMPS + 1; ++j) {
        printf("thread1: [%d] %s", j, ctime(&timers[j]));
    }
    printf("thread1: done\n");
}

void *threadn() {
    print_current_thread_priority("threadn");
    time_t timers[TIMESTAMPS + 1];
    int next_timestamp = 0;
    for (int i = 0; i <= MAX_COUNT; ++i) {
        if (i % (MAX_COUNT / TIMESTAMPS) == 0) {
            timers[next_timestamp++] = time(0);
        }
    }
    for (int j = 0; j < TIMESTAMPS + 1; ++j) {
        printf("threadn: [%d] %s", j, ctime(&timers[j]));
    }
    printf("threadn: done\n");
}

int main(int argc, char **argv) {
    pthread_t t1;
    pthread_t tn;
    set_priority(0, SCHED_RR, 30);
    print_current_priority("main");
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&tn, NULL, threadn, NULL);
    pthread_join(t1, NULL);
    pthread_join(tn, NULL);
    return 0;
}