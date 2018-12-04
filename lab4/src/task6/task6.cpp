#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

DWORD WINAPI threadHandler(LPVOID);

struct Params {
    int num;
    bool *runFlag;
};
long long counters[7] = {0, 0, 0, 0, 0, 0, 0};
int priority[7] = {THREAD_PRIORITY_IDLE, THREAD_PRIORITY_LOWEST,
                   THREAD_PRIORITY_BELOW_NORMAL, THREAD_PRIORITY_NORMAL,
                   THREAD_PRIORITY_ABOVE_NORMAL, THREAD_PRIORITY_HIGHEST,
                   THREAD_PRIORITY_TIME_CRITICAL};

void useSingleCore();

int main(int argc, char *argv[]) {
    int stop = argc > 1 ? atoi(argv[1]) : 5000;
    useSingleCore();
    bool runFlag = true;
    HANDLE tm1 = CreateWaitableTimer(NULL, false, NULL);
    __int64 endTime = -1 * stop * 10000000;
    LARGE_INTEGER timerEndTime;
    timerEndTime.LowPart = (DWORD) (endTime & 0xFFFFFFFF);
    timerEndTime.HighPart = (LONG) (endTime >> 32);
    SetWaitableTimer(tm1, &timerEndTime, 0, NULL, NULL, false);
    for (int i = 0; i < 7; i++) {
        Params *param = (Params *) malloc(sizeof(Params));
        param->num = i;
        param->runFlag = &runFlag;
        DWORD targetThreadId;
        HANDLE handle = CreateThread(NULL, 0, threadHandler, param, 0, &targetThreadId);
        SetThreadPriority(handle, priority[i]);
        cout << i << ": priority is " << GetThreadPriority(handle) << endl;
        SetThreadPriorityBoost(handle, true);
        CloseHandle(handle);
    }
    WaitForSingleObject(tm1, INFINITE);
    runFlag = false;
    CloseHandle(tm1);
    for (int i = 0; i < 7; i++) {
        cout << i << ": counter = " << counters[i] << endl;
    }
    return 0;
}

void useSingleCore() {
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
    SetProcessAffinityMask(process, processAffinityMask);
}

DWORD WINAPI threadHandler(LPVOID prm) {
    Params arg = *((Params *) prm);
    DWORD WINAPI threadId = GetCurrentThreadId();
    HANDLE WINAPI handle = OpenThread(THREAD_QUERY_INFORMATION, false, threadId);
    while (true) {
        int WINAPI threadPriority = GetThreadPriority(handle);
        counters[arg.num]++;
        if (threadPriority != priority[arg.num]) {
            cout << arg.num << ": priority is " << priority[arg.num]
                 << " " << threadPriority << "changed" << endl;
        }
        Sleep(0);
        if (!*(arg.runFlag)) {
            break;
        }
    }
    return 1;
}
