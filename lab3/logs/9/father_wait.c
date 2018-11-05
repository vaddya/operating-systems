#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int pid[4], status[3], result[3];
    char *sons[] = {"son1", "son2", "son3"};
    int option[] = {WNOHANG, WUNTRACED, WNOHANG};
    pid[3] = getpid();
    int ppid = getppid();
    printf("father params: PID = %i, PPID = %i\n", pid[3], ppid);
    for (int i = 0; i < 3; i++) {
        if ((pid[i] = fork()) == 0) {
            execl(sons[i], sons[i], NULL);
        }
    }
    system("ps xf > dump.txt");
    for (int i = 0; i < 3; i++) {
        result[i] = waitpid(pid[i], &status[i], option[i]);
        printf("%d) child process with pid = %d is finished with status %d\n", i + 1, result[i], status[i]);
    }
    for (int i = 0; i < 3; i++) {
        if (WIFEXITED(status[i]) == 0)
            printf("process pid = %d was failed.\n", pid[i]);
        else
            printf("process pid = %d was success, code = %d\n", pid[i], WEXITSTATUS(status[i]));
    }
    return 0;
}
