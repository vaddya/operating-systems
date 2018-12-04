#include <cstdio>
#include <windows.h>
#include <iostream>

#define DEF_BUFLEN 100

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    cout << "Program started" << endl;
    if (argc < 2) {
        cout << "Input name of configuration file" << endl;
        return 999;
    }
    const char *frd = argv[1];
    FILE *f = fopen(frd, "r");
    if (f == NULL) {
        cout << "Error opening file: " << argv[1] << endl;
        return 1000;
    }
    char commandLine[DEF_BUFLEN];
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;
    while (!feof(f)) {
        ZeroMemory(commandLine, DEF_BUFLEN);
        fgets(commandLine, DEF_BUFLEN, f);
        if (strlen(commandLine) <= 1) {
            cout << "Skipping empty string" << endl;
            continue;
        }
        commandLine[strlen(commandLine) - 1] = '\0';
        ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
        startupInfo.cb = sizeof(STARTUPINFO);
        cout << "Try to create new process with command line '" << commandLine << "'" << endl;
        if (!CreateProcess(NULL, commandLine, NULL, NULL, false, 0, NULL, NULL, &startupInfo, &processInformation)) {
            cout << "Can't create new process. Error is: " << GetLastError() << endl
                 << "Continue with next line" << endl;
            continue;
        }
        cout << "New process handle: " << processInformation.dwProcessId << endl
             << "Handle of thread: " << processInformation.dwThreadId << endl;
        CloseHandle(processInformation.hThread);
        CloseHandle(processInformation.hProcess);
    }
    fclose(f);
    cout << "Program finished" << endl;
    return 0;
}