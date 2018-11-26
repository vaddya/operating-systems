#include <windows.h>
#include <iostream>

#define MAX_LEN 200

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    const char *frd = "temp.txt";
    FILE *f = fopen(frd, "r");
    if (f == NULL) {
        cout << "Couldn't open file" << endl;
        return 1;
    }
    for (int i = 0; i < 2; i++) {
        char *execString = (char *) calloc(MAX_LEN, sizeof(char));
        fgets(execString, MAX_LEN, f);
        execString[strlen(execString) - 1] = '\0';
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
        startupInfo.cb = sizeof(startupInfo);
        PROCESS_INFORMATION processInfo;
        cout << execString << endl;
        if (!CreateProcess(NULL, execString, NULL, NULL, false, 0, NULL, NULL, &startupInfo, &processInfo)) {
            cout << "Error creating process: " << GetLastError() << endl;
            return -1;
        } else {
            printf("Process successfully created!\n");
        }
        free(execString);
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
    }
    return 0;
}