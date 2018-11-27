#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <iostream>

const char *message = "Message from parent\n";

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE fileHandle = CreateFile("file.txt", GENERIC_WRITE, 0, &sa, OPEN_ALWAYS, 0, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        cerr << "create file error: " << GetLastError() << endl;
        return -1;
    }
    cout << "file handle: " << fileHandle;
    DWORD written;
    DWORD len = strlen(message);
    WriteFile(fileHandle, message, len, &written, NULL);
    if (written != len) {
        cerr << "write error: " << GetLastError() << endl;
        return -1;
    }
    STARTUPINFO startupInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo;
    char buf[100];
    sprintf(buf, "%s %d", "../son/son.exe", (int) fileHandle);
    if (!CreateProcess(NULL, buf, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo)) {
        cerr << "create process error: " << GetLastError() << endl;
        return -1;
    }
    Sleep(100);
    WriteFile(fileHandle, message, len, &written, NULL);
    if (written != len) {
        cerr << "write error: " << GetLastError() << endl;
        return -1;
    }
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
    CloseHandle(fileHandle);
    return 0;
}