#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

DWORD WINAPI Thread1(LPVOID);

struct Params {
    int num;
    bool *runflg;
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
        param->runflg = &runFlag;
        DWORD targetThreadId;
        HANDLE t1 = CreateThread(NULL, 0, Thread1, param, 0, &targetThreadId);
        SetThreadPriority(t1, priority[i]);
        PBOOL ptr1 = (PBOOL) malloc(sizeof(BOOL));
        GetThreadPriorityBoost(t1, ptr1);
        SetThreadPriorityBoost(t1, true);
        CloseHandle(t1);
    }
    WaitForSingleObject(tm1, INFINITE);
    runFlag = false;
    CloseHandle(tm1);
    for (int i = 0; i < 7; i++) {
        cout << i << ": " << counters[i] << endl;
    }
    return 0;
}

void useSingleCore() {
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
    SetProcessAffinityMask(process, processAffinityMask);
}

DWORD WINAPI Thread1(LPVOID prm) {
    while (true) {
        DWORD WINAPI threadId = GetCurrentThreadId();
        HANDLE WINAPI handle = OpenThread(THREAD_QUERY_INFORMATION, false, threadId);
        int WINAPI threadPriority = GetThreadPriority(handle);
        Params arg = *((Params *) prm);
        counters[arg.num]++;
        if (threadPriority != priority[arg.num]) {
            cout << "Priority of " << arg.num << " is "
                 << priority[arg.num] << " " << threadPriority << "changed" << endl;
        }
        Sleep(0);
        if (!*(arg.runflg)) {
            break;
        }
    }
    return 1;
}
