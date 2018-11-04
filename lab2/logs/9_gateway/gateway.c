#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if (setuid(geteuid()) != 0) {
        fputs(strerror(errno), stderr);
        return 1;
    }

    system("cat root_file");
    return 0;
}
