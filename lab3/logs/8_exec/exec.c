#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *file = "ls";
    char *path = "/bin/ls";
    char *args[] = {"ls", "-l", NULL};
    char *env[] = {(char *) NULL};
    int pid;
    if (pid = fork() == 0) {
        switch ((int) argv[1][0]) {
            case (int) '1':
                execl(path, file, "-l", (char *) NULL);
                break;
            case (int) '2':
                execlp(file, file, "-l", (char *) NULL);
                break;
            case (int) '3':
                execle(path, file, "-l", (char *) NULL, env);
                break;
            case (int) '4':
                execv(path, args);
                break;
            case (int) '5':
                execvp(file, args);
                break;
            case (int) '6':
                execvpe(file, args, (char *) NULL, env);
                break;
        }
    }
    return 0;
}