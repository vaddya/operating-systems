#include <windows.h>
#include <iostream>

const int BUF_SIZE = 100;
const char *clientName = "../tcp_client/pipe_echo_client.exe";

int main(int argc, char *argv[]) {
    HANDLE readPipeFromServerToClient, writePipeFromServerToClient;
    HANDLE readPipeFromClientToServer, writePipeFromClientToServer;
    SECURITY_ATTRIBUTES pipeSecAttr = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    if (CreatePipe(&readPipeFromServerToClient, &writePipeFromServerToClient, &pipeSecAttr, 0) == 0) {
        printf("Impossible to create anonymous pipe from server to client\n");
        return 1;
    }
    if (CreatePipe(&readPipeFromClientToServer, &writePipeFromClientToServer, &pipeSecAttr, 0) == 0) {
        printf("Impossible to create anonymous pipe from client to server\n");
        return 1;
    }
    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo;
    GetStartupInfo(&startupInfo);
    startupInfo.hStdInput = readPipeFromServerToClient;
    startupInfo.hStdOutput = writePipeFromClientToServer;
    startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    startupInfo.dwFlags = STARTF_USESTDHANDLES;
    CreateProcess(NULL, (LPSTR) clientName, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo);
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
    CloseHandle(readPipeFromServerToClient);
    CloseHandle(writePipeFromClientToServer);
    BYTE buf[BUF_SIZE];
    DWORD readbytes, writebytes;
    for (int i = 0; i < 10; i++) {
        if (!ReadFile(readPipeFromClientToServer, buf, BUF_SIZE, &readbytes, NULL)) {
            printf("Impossible to use readfile\n GetLastError= %ld\n", GetLastError());
            break;
        }
        printf("Got msg from client: \"%s\"\n", buf);
        if (!WriteFile(writePipeFromServerToClient, buf, readbytes, &writebytes, NULL)) {
            printf("Impossible to use writefile\n GetLastError= %ld\n", GetLastError());
            break;
        }
    }
    CloseHandle(readPipeFromClientToServer);
    CloseHandle(writePipeFromServerToClient);
    system("pause");
    return 0;
}
