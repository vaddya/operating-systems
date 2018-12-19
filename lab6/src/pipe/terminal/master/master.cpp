#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

const char *slaveName = "../slave/pipe_terminal_slave.exe";

int main(int argc, char *argv[]) {
    STARTUPINFO si = {sizeof(si)};
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi;
    char buf[1024];
    HANDLE newstdread, newstdwrite;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = true;
    if (!CreatePipe(&newstdread, &newstdwrite, &sa, 0)) {
        cerr << "CreatePipe error";
        return 1;
    }
    cout << "Pipe is created!" << endl;
    cout << "The read HANDLE of PIPE = " << newstdread << endl;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_NORMAL;
    si.hStdInput = newstdread;
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = si.hStdOutput;
    if (!CreateProcess(NULL, (LPSTR) slaveName, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cerr << "CreateProcess error" << endl;
        CloseHandle(newstdread);
        CloseHandle(newstdwrite);
        return 1;
    }
    cout << "Process is created" << endl;
    memset(buf, '\0', sizeof(buf));
    cout << buf;
    unsigned long bread;
    cout << "STD INPUT HANDLE = " << GetStdHandle(STD_INPUT_HANDLE) << endl;
    cout << "STD OUTPUT HANDLE = " << GetStdHandle(STD_OUTPUT_HANDLE) << endl;
    while (true) {
        memset(buf, '\0', sizeof(buf));
        *buf = (char) getch();
        cout.put(*buf);
        if (*buf == 13) {
            *buf = '\n';
            cout.put(*buf);
        }
        WriteFile(newstdwrite, buf, 1, &bread, NULL);
        if (*buf == 27) {
            break;
        }
    }
    system("pause");
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(newstdread);
    CloseHandle(newstdwrite);
    return 0;
}