#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    for (int i = 0; i < 10; i++) {
        printf("%d\n ", i);
        sleep(2);
    }
    return 0;
}