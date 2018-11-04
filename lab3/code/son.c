#include <stdio.h>

int main() {
	int pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("\n\nSON PARAMS: pid=%i ppid=%i\n\n", pid, ppid);
	sleep(15);
	return 0; // статус завершения 0
}
