#include <cstdio>
#include <windows.h>

DWORD WINAPI Thread1(LPVOID);

int stop;
struct Params {
    int num;
    bool *runflg;
};

void printTime() {
    SYSTEMTIME now;
    GetSystemTime(&now);
    printf("System Time %d %d %d\n", now.wHour, now.wMinute, now.wSecond);
}

int main(int argc, char *argv[]) {
    int thrds = argc < 3 ? 2 : atoi(argv[1]);
    stop = argc < 3 ? 5000 : atoi(argv[2]);
    DWORD targetThreadId;
    bool runFlag = true;
    __int64 end_time = -1 * stop * 10000000;
    LARGE_INTEGER end_time2;
    end_time2.LowPart = (DWORD) (end_time & 0xFFFFFFFF);
    end_time2.HighPart = (LONG) (end_time >> 32);
    HANDLE tm1 = CreateWaitableTimer(NULL, false, NULL);
    SetWaitableTimer(tm1, &end_time2, 0, NULL, NULL, false);
    for (int i = 0; i < thrds; i++) {
        Params *param = (Params *) malloc(sizeof(Params));
        param->num = i;
        param->runflg = &runFlag;
        HANDLE t1 = CreateThread(NULL, 0, Thread1, param, 0, &targetThreadId);
        CloseHandle(t1);
    }
    printTime();
    WaitForSingleObject(tm1, INFINITE);
    runFlag = false;
    CloseHandle(tm1);
    printTime();
    return 0;
}

DWORD WINAPI Thread1(LPVOID arg) {
    while (true) {
        Params params = *((Params *) arg);
        Sleep(1000);
        printf("%d\n", params.num);
        if (!*(params.runflg))
            break;
    }
    return 0;
} 