#include <cstdio>
#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

DWORD WINAPI threadHandler(LPVOID);

int main(int argc, char *argv[]) {
    printf("Program started\n");
    HANDLE t;
    int number = 1;
    t = CreateThread(NULL, 0, threadHandler, (LPVOID) number, 0, NULL);
    CloseHandle(t);
    number = 2;
    t = CreateThread(NULL, 0, threadHandler, (LPVOID) number, 0, NULL);
    CloseHandle(t);
    ExitThread(0);
    cout << "Program finished" << endl;
    system("pause");
    return 0;
}

DWORD WINAPI threadHandler(LPVOID param) {
    int number = (int) param;
    for (;;) {
        Sleep(1000);
        cout << number;
    }
    return 0;
}
