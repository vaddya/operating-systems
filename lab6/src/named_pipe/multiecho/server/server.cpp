#include <windows.h>
#include <iostream>

const char *pipeName = R"(\\.\pipe\$MyPipe$)";
const int BUF_SIZE = 1000;

DWORD WINAPI threadHandler(HANDLE namedPipe) {
    char buf[BUF_SIZE];
    DWORD readbytes, writebytes;
    while (true) {
        if (!ReadFile(namedPipe, buf, BUF_SIZE, &readbytes, NULL)) {
            printf("ReadFile: Error %ld\n", GetLastError());
            break;
        }
        if (!WriteFile(namedPipe, buf, strlen(buf) + 1, &writebytes, NULL)) {
            printf("WriteFile: Error %ld\n", GetLastError());
            break;
        }
        printf("Get client msg: %s\n", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }
    }
    CloseHandle(namedPipe);
    return 0;
}

int main(int argc, char *argv[]) {
    printf("Server is started. Trying to create named pipe\n");
    SECURITY_DESCRIPTOR sd;
    if (InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) == 0) {
        printf("InitializeSecurityDescriptor failed with error %ld\n", GetLastError());
        return 1;
    }
    if (SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE) == 0) {
        printf("SetSecurityDescriptorDacl failed with error %ld\n", GetLastError());
        return 1;
    }
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = FALSE;
    DWORD pipeMode = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;
    DWORD maxInst = 5;
    while (true) {
        HANDLE namedPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, pipeMode, maxInst, BUF_SIZE, BUF_SIZE, 5000, &sa);
        if (namedPipe == INVALID_HANDLE_VALUE) {
            printf("CreateNamedPipe: Error %ld\n", GetLastError());
            return 1;
        }
        printf("Named pipe was created\nWaiting for connect...\n");
        if (!ConnectNamedPipe(namedPipe, NULL)) {
            printf("Error while connecting to named pipe\n");
            CloseHandle(namedPipe);
            return 1;
        }
        printf("Client connected\n");
        HANDLE thread = CreateThread(NULL, 0, threadHandler, (LPVOID) namedPipe, 0, NULL);
        if (thread == NULL) {
            printf("CreateThread: Error %ld\n", GetLastError());
            break;
        }
        CloseHandle(thread);
    }
    return 0;
}