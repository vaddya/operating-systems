#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <iostream>

const char *message = "Message from parent\n";

using namespace std;

int main(int argc, char *argv[]) {
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE fileHandle = CreateFile("file.txt", GENERIC_WRITE, 0, &sa, TRUNCATE_EXISTING, 0, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        cerr << "create file error: " << GetLastError() << endl;
        return -1;
    }
    cout << "file handle: " << fileHandle << endl;
    DWORD written;
    DWORD length = strlen(message);
    WriteFile(fileHandle, message, length, &written, NULL);
    if (written != length) {
        cerr << "write error: " << GetLastError() << endl;
        return -1;
    }
    STARTUPINFO startupInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo;
    char buf[100];
    sprintf(buf, "../son/son.exe %d", (int) fileHandle);
    cout << "creating process: " << buf << endl;
    if (!CreateProcess(NULL, buf, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo)) {
        cerr << "create process error: " << GetLastError() << endl;
        return -1;
    }
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
    CloseHandle(fileHandle);
    return 0;
}
