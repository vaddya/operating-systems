#include <windows.h>
#include <iostream>

const int BUF_SIZE = 128;

int main(int argc, char *argv[]) {
    char sendBuf[BUF_SIZE];
    char recvBuf[BUF_SIZE];
    int sendCount;
    DWORD wasSendCount, wasReadCount;
    for (int i = 0; i < 10; i++) {
        sendCount = sprintf(sendBuf, "message num %d", i + 1);
        sendBuf[sendCount] = 0;
        fprintf(stderr, "client send: \"%s\"\n", sendBuf);
        if (!WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), sendBuf, sendCount + 1, &wasSendCount, NULL)) {
            fprintf(stderr, "Error with writeFile\n Wait 5 sec GetLastError= %d\n", GetLastError());
            system("pause");
            return 1;
        }
        if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), recvBuf, BUF_SIZE, &wasReadCount, NULL)) {
            fprintf(stderr, "Error with readFile\n Wait 5 sec GetLastError= %d\n", GetLastError());
            system("pause");
            return 1;
        }
        fprintf(stderr, "Got msg from server: \"%s\"\n", recvBuf);
    }
    system("pause");
    return 0;
}
