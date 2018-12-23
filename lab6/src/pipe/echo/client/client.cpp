#include <windows.h>
#include <iostream>

const int BUF_SIZE = 100;

int main(int argc, char *argv[]) {
    char sendBuffer[BUF_SIZE];
    char recvBuffer[BUF_SIZE];
    int sendCount;
    DWORD wasSendCount, wasReadCount;
    for (int i = 0; i < 10; i++) {
        sendCount = sprintf(sendBuffer, "message num %d", i + 1);
        sendBuffer[sendCount] = 0;
        fprintf(stderr, "client send: \"%s\"\n", sendBuffer);
        if (!WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), sendBuffer, sendCount + 1, &wasSendCount, NULL)) {
            fprintf(stderr, "Error with writeFile\n Wait 5 sec GetLastError= %d\n", GetLastError());
            system("pause");
            return 1;
        }
        if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), recvBuffer, BUF_SIZE, &wasReadCount, NULL)) {
            fprintf(stderr, "Error with readFile\n Wait 5 sec GetLastError= %d\n", GetLastError());
            system("pause");
            return 1;
        }
        fprintf(stderr, "Gщt msg from server: \"%s\"\n", recvBuffer);
    }
    system("pause");
    return 0;
}
