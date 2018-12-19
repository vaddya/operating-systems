#include <windows.h>
#include <iostream>

const int BUF_SIZE = 100;
const char *pipeTemplate = "../client/pipe_echo_client.exe";

int main(int argc, char *argv[]) {
    HANDLE hReadPipeFromServerToClient, hWritePipeFromServerToClient;
    HANDLE hReadPipeFromClientToServer, hWritePipeFromClientToServer;
    SECURITY_ATTRIBUTES pipeSecAttr = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    if (CreatePipe(&hReadPipeFromServerToClient, &hWritePipeFromServerToClient, &pipeSecAttr, 0) == 0) {
        printf("impossible to create anonymous pipe from server to client\n");
        return 1;
    }
    if (CreatePipe(&hReadPipeFromClientToServer, &hWritePipeFromClientToServer, &pipeSecAttr, 0) == 0) {
        printf("impossible to create anonymous pipe from client to serv\n");
        return 1;
    }
    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo;
    GetStartupInfo(&startupInfo);
    startupInfo.hStdInput = hReadPipeFromServerToClient;
    startupInfo.hStdOutput = hWritePipeFromClientToServer;
    startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    startupInfo.dwFlags = STARTF_USESTDHANDLES;
    CreateProcess(NULL, (LPSTR) pipeTemplate, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo);
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
    CloseHandle(hReadPipeFromServerToClient);
    CloseHandle(hWritePipeFromClientToServer);
    BYTE buf[BUF_SIZE];
    DWORD readbytes, writebytes;
    for (int i = 0; i < 10; i++) {
        if (!ReadFile(hReadPipeFromClientToServer, buf, BUF_SIZE, &readbytes, NULL)) {
            printf("impossible to use readfile\n GetLastError= %d\n", GetLastError());
            break;
        }
        printf("get from client: \"%s\"\n", buf);
        if (!WriteFile(hWritePipeFromServerToClient, buf, readbytes, &writebytes, NULL)) {
            printf("impossible to use writefile\n GetLastError= %d\n", GetLastError());
            break;
        }
    }
    CloseHandle(hReadPipeFromClientToServer);
    CloseHandle(hWritePipeFromServerToClient);
    system("pause");
    return 0;
}