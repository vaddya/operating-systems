#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

DWORD WINAPI threadHandler(LPVOID);

struct Params {
    int num;
    bool *runFlag;
};

void printTime() {
    SYSTEMTIME now;
    GetSystemTime(&now);
    cout << "System Time " << now.wHour << ":" << now.wMinute << ":" << now.wSecond << endl;
}

int main(int argc, char *argv[]) {
    int threads = argc < 3 ? 2 : atoi(argv[1]);
    int stop = argc < 3 ? 5000 : atoi(argv[2]);
    DWORD targetThreadId;
    bool runFlag = true;
    __int64 end_time = -1 * stop * 10000000;
    LARGE_INTEGER end_time2;
    end_time2.LowPart = (DWORD) (end_time & 0xFFFFFFFF);
    end_time2.HighPart = (LONG) (end_time >> 32);
    HANDLE tm1 = CreateWaitableTimer(NULL, false, NULL);
    SetWaitableTimer(tm1, &end_time2, 0, NULL, NULL, false);
    for (int i = 0; i < threads; i++) {
        Params *param = (Params *) malloc(sizeof(Params));
        param->num = i;
        param->runFlag = &runFlag;
        HANDLE t1 = CreateThread(NULL, 0, threadHandler, param, 0, &targetThreadId);
        CloseHandle(t1);
    }
    printTime();
    WaitForSingleObject(tm1, INFINITE);
    runFlag = false;
    CloseHandle(tm1);
    printTime();
    return 0;
}

DWORD WINAPI threadHandler(LPVOID arg) {
    Params params = *((Params *) arg);
    while (true) {
        Sleep(1000);
        cout << params.num << " ";
        if (!*(params.runFlag)) {
            break;
        }
    }
    cout << endl;
    return 0;
}
