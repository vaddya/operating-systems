#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>

using namespace std;

const char *message = "Message from son\n";

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "argv error: file handle" << endl;
        return -1;
    }
    HANDLE fileHandle = (HANDLE) atoi(argv[1]);
    cout << "file handle: " << fileHandle << endl;
    DWORD written;
    DWORD length = strlen(message);
    WriteFile(fileHandle, message, length, &written, NULL);
    if (written != length) {
        cerr << "write error: " << GetLastError() << endl;
        system("pause");
        return -1;
    }
    system("pause");
    CloseHandle(fileHandle);
    return 0;
}