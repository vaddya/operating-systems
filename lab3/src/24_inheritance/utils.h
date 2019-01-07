#ifndef LOGSUTILSH
#define LOGSUTILSH

void print_current_priority(char *id);

void print_current_thread_priority(char *id);

void set_priority(int pid, int policy, int priority);

void set_thread_priority(int policy, int priority);

#endif //LOGSUTILSH
