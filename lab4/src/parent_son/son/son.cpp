#include <windows.h>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

const char *message = "Message from son\n";

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "file handle must be an argument" << endl;
        return -1;
    }
    HANDLE fileHandle = (HANDLE) atoi(argv[1]);
    cout << "file handle: " << fileHandle << endl;
    DWORD written;
    DWORD len = strlen(message);
    WriteFile(fileHandle, message, len, &written, NULL);
    if (written != len) {
        cout << "write error: " << GetLastError() << endl;
        CloseHandle(fileHandle);
        system("pause");
        return -1;
    }
    CloseHandle(fileHandle);
    system("pause");
    return 0;
}