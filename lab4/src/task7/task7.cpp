#include <cstdio>
#include <windows.h>

#define DEF_THREADS 7
#define DEF_TTL 10

void useSingleCore();

DWORD WINAPI threadHandler(LPVOID);

HANDLE initTimer(int sec);

int getPriorityIndex(DWORD prClass);

int isFinish = 0;
long counters[7] = {0, 0, 0, 0, 0, 0, 0};
int priorities[7] = {THREAD_PRIORITY_IDLE, THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_BELOW_NORMAL, THREAD_PRIORITY_NORMAL,
                     THREAD_PRIORITY_ABOVE_NORMAL, THREAD_PRIORITY_HIGHEST, THREAD_PRIORITY_TIME_CRITICAL};
char charPriorities[7][10] = {"IDLE", "LOWEST", "BELOW", "NORMAL", "ABOVE", "HIGHEST", "TIME_CRIT"};
DWORD procPriorities[6] = {IDLE_PRIORITY_CLASS, BELOW_NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS,
                           ABOVE_NORMAL_PRIORITY_CLASS, HIGH_PRIORITY_CLASS, REALTIME_PRIORITY_CLASS};
char charProcPriorities[6][10] = {"IDLE", "BELOW", "NORMAL", "ABOVE", "HIGH", "REALTIME"};
int priorityBoost[7] = {0, 0, 0, 0, 0, 0, 0};
int priorityChange[7] = {0, 0, 0, 0, 0, 0, 0};

int main(int argc, char *argv[]) {
    useSingleCore();
    int numThreads = DEF_THREADS;
    int threadLive = DEF_TTL;
    if (argc < 3) {
        printf("Using default numThreads = %d and default time to live = %d\n", numThreads, threadLive);
    } else {
        numThreads = atoi(argv[1]);
        threadLive = atoi(argv[2]);
        if (numThreads <= 0 || threadLive <= 0) {
            printf("All arguments must be numbers!!!!\n");
            return 1;
        }
    }
    HANDLE t = initTimer(threadLive);
    HANDLE t1;
    SetPriorityClass(GetCurrentProcess(), procPriorities[4]);
    for (int i = 0; i < numThreads; i++) {
        t1 = CreateThread(NULL, 0, threadHandler, (LPVOID) i, 0, NULL);
        SetThreadPriority(t1, priorities[i]);
        SetThreadPriorityBoost(t1, true);
        GetThreadPriorityBoost(t1, &priorityBoost[i]);
        CloseHandle(t1);
    }
    WaitForSingleObject(t, INFINITE);
    CloseHandle(t);
    isFinish = 1;
    char hasBoost[4];
    char wasChanged[4];
    int priorIdx = getPriorityIndex(GetPriorityClass(GetCurrentProcess()));
    printf("Result of work:\n");
    printf("Process priority: %s\n", charProcPriorities[priorIdx]);
    printf("Priority\tHas Boost\tWas changed\tCounter\n");
    for (int i = 0; i < 7; i++) {
        strcpy_s(hasBoost, priorityBoost[i] == 0 ? "NO" : "YES");
        strcpy_s(wasChanged, priorityChange[i] == 0 ? "NO" : "YES");
        printf("%9s\t%9s\t%10s\t%7d\n", charPriorities[i], hasBoost, wasChanged, counters[i]);
    }
    return 0;
}

void useSingleCore() {
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
    SetProcessAffinityMask(process, processAffinityMask);
}

DWORD WINAPI threadHandler(LPVOID prm) {
    int myNum = (int) prm;
    int priority = 0;
    while (true) {
        ++counters[myNum];
        priority = GetThreadPriority(GetCurrentThread());
        if (priority != priorities[myNum]) {
            priorityChange[myNum] = 1;
        }
        if (isFinish) {
            break;
        }
        Sleep(0);
    }
    return 0;
}

HANDLE initTimer(int sec) {
    __int64 endTime;
    LARGE_INTEGER timerEndTime;
    HANDLE tm = CreateWaitableTimer(NULL, false, "timer");
    endTime = -1 * sec * 10000000;
    timerEndTime.LowPart = (DWORD) (endTime & 0xFFFFFFFF);
    timerEndTime.HighPart = (LONG) (endTime >> 32);
    SetWaitableTimer(tm, &timerEndTime, 0, NULL, NULL, false);
    return tm;
}

int getPriorityIndex(DWORD prClass) {
    for (int i = 0; i < 6; ++i) {
        if (procPriorities[i] == prClass)
            return i;
    }
    return 0;
}
