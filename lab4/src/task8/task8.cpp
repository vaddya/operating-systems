#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;

HANDLE processHandle, mainThread, secondThread;

void thread() {
    while (true) {
        Sleep(2000);
    }
}

void printPriorityBoosts() {
    BOOL dynamic;
    GetProcessPriorityBoost(processHandle, &dynamic);
    cout << "Process dynamically default is " << dynamic << endl;
    GetThreadPriorityBoost(mainThread, &dynamic);
    cout << "Main thread dynamic default is " << dynamic << endl;
    GetThreadPriorityBoost(secondThread, &dynamic);
    cout << "Second thread dynamic default is " << dynamic << endl << endl;
}

int main(int argc, char *argv[]) {
    processHandle = GetCurrentProcess();
    mainThread = GetCurrentThread();
    secondThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) thread, NULL, 0, NULL);
    cout << "0 - dynamic enabled, 1 - disabled." << endl << endl;

    // default values
    cout << "Default values:" << endl;
    printPriorityBoosts();

    // change thread dynamically
    cout << "Change thread dynamic priority:" << endl;
    if (!SetThreadPriorityBoost(secondThread, true)) {
        cout << "Error on thread change!" << endl;
        return 2;
    }
    printPriorityBoosts();

    // change process dynamically
    cout << "Change process dynamic priority:" << endl;
    if (!SetProcessPriorityBoost(processHandle, true)) {
        cout << "Error on priority change!" << endl;
        return 1;
    }
    printPriorityBoosts();

    // may be can change thread dynamic priority?
    cout << "Change thread dynamic priority:" << endl;
    if (!SetThreadPriorityBoost(secondThread, false)) {
        cout << "We cannot change if process ban dynamic priority!" << endl;
        return 3;
    }
    printPriorityBoosts();
    return 0;
}
