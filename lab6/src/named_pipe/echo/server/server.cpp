#include <windows.h>
#include <iostream>
#include <conio.h>

const char *pipeTemplate = R"(\\.\pipe\$MyPipe$)";
const int BUFFER_SIZE = 512;

int main(int argc, char *argv[]) {
    DWORD pipeMode = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;
    HANDLE hNamedPipe = CreateNamedPipe(pipeTemplate, PIPE_ACCESS_DUPLEX, pipeMode, PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);
    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        fprintf(stdout, "CreateNamedPipe: Error %ld\n", GetLastError());
        getch();
        return 1;
    }
    printf("Named pipe was created\n");
    printf("Waiting for connect...\n");
    if (!ConnectNamedPipe(hNamedPipe, NULL)) {
        switch (GetLastError()) {
            case ERROR_NO_DATA:
                printf("ConnectNamedPipe: ERROR_NO_DATA\n");
                break;
            case ERROR_PIPE_CONNECTED:
                printf("ConnectNamedPipe: ERROR_PIPE_CONNECTED\n");
                break;
            case ERROR_PIPE_LISTENING:
                printf("ConnectNamedPipe: ERROR_PIPE_LISTENING\n");
                break;
            case ERROR_CALL_NOT_IMPLEMENTED:
                printf("ConnectNamedPipe: ERROR_CALL_NOT_IMPLEMENTED\n");
                break;
            default:
                printf("ConnectNamedPipe: Error %ld\n", GetLastError());
                break;
        }
        CloseHandle(hNamedPipe);
        getch();
        return 1;
    }
    printf("Connected. Waiting for command...\n");
    char buf[BUFFER_SIZE];
    DWORD cbRead;
    DWORD cbWritten;
    while (true) {
        if (!ReadFile(hNamedPipe, buf, BUFFER_SIZE, &cbRead, NULL)) {
            printf("ReadFile: Error %ld\n", GetLastError());
            getch();
            break;
        }
        printf("Received: <%s>\n", buf);
        if (!WriteFile(hNamedPipe, buf, strlen(buf) + 1, &cbWritten, NULL)) {
            printf("WriteFile: Error %ld\n", GetLastError());
            break;
        }
        if (!strcmp(buf, "exit")) {
            break;
        }
    }
    CloseHandle(hNamedPipe);
    return 0;
}