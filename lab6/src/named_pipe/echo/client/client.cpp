#include <windows.h>
#include <iostream>
#include <conio.h>

const char *pipeTemplate = R"(\\.\pipe\$MyPipe$)";
const int BUFFER_SIZE = 256;

int main(int argc, char *argv[]) {
    printf("Named pipe client demo\n");
    printf("Syntax: pipec [servername]\n");
    DWORD accessMode = GENERIC_READ | GENERIC_WRITE;
    HANDLE hNamedPipe = CreateFile(pipeTemplate, accessMode, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        printf("CreateFile: Error %ld\n", GetLastError());
        getch();
        return 1;
    }
    printf("Connected. Type 'exit' to terminate\n");
    char buf[BUFFER_SIZE];
    DWORD cbWritten;
    DWORD cbRead;
    while (true) {
        printf(">");
        gets(buf);
        if (!WriteFile(hNamedPipe, buf, strlen(buf) + 1, &cbWritten, NULL)) {
            printf("WriteFile: Error %ld\n", GetLastError());
            break;
        }
        if (!ReadFile(hNamedPipe, buf, BUFFER_SIZE, &cbRead, NULL)) {
            printf("ReadFile: Error %ld\n", GetLastError());
            break;
        }
        printf("Received back: <%s>\n", buf);
        if (!strcmp(buf, "exit")) {
            break;
        }
    }
    CloseHandle(hNamedPipe);
    return 0;
}