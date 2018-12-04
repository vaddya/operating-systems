#include <windows.h>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    cout << "Program started" << endl;
    char commandLine[60];
    strcpy_s(commandLine, R"(C:\WINDOWS\system32\notepad.exe)");
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(startupInfo);
    DWORD creationFlags = HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
    if (!CreateProcess(NULL, commandLine, NULL, NULL, false, creationFlags, NULL, NULL, &startupInfo, &processInfo)) {
        cout << "Error creating process: " << GetLastError() << endl;
        return -1;
    } else {
        cout << "New process handle: " << processInfo.dwProcessId << endl
             << "Handle of thread: " << processInfo.dwThreadId << endl
             << "Successfully created new process!" << endl;
    }
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
    cout << "Program finished" << endl;
    return 0;
}
