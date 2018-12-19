#include <windows.h>
#include <iostream>

const char *pipeTemplate = R"(\\%s\pipe\$MyPipe$)";
const int BUF_SIZE = 1000;

int main(int argc, char *argv[]) {
    printf("Client is started\n");
    char pipeName[100];
    memset(pipeName, 0, 100);
    sprintf(pipeName, pipeTemplate, argc < 2 ? "." : argv[1]);
    printf("Using pipe name: %s\n", pipeName);
    printf("Trying to use WaitNamedPipe\n");
    if (!WaitNamedPipe(pipeName, NMPWAIT_WAIT_FOREVER)) {
        printf("Pipe wasn't created\n GetLastError = %ld", GetLastError());
        return 1;
    }
    HANDLE hNamedPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        printf("CreateFile: Error %ld\n", GetLastError());
        return 1;
    }
    printf("Successfully connected\n Input message:\n");
    char buf[BUF_SIZE];
    DWORD readbytes, writebytes;
    while (true) {
        printf("$ ");
        fgets(buf, BUF_SIZE, stdin);
        if (!WriteFile(hNamedPipe, buf, strlen(buf) + 1, &writebytes, NULL)) {
            printf("WriteFile: Error %ld\n", GetLastError());
            break;
        }
        if (!ReadFile(hNamedPipe, buf, BUF_SIZE, &readbytes, NULL)) {
            printf("ReadFile: Error %ld\n", GetLastError());
            getchar();
            break;
        }
        printf("Received from server: %s", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }
    }
    CloseHandle(hNamedPipe);
    system("pause");
    return 0;
}