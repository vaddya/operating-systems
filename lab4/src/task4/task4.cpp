#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

DWORD WINAPI threadHandler(LPVOID);

int main(int argc, char *argv[]) {
    cout << "Program started\n";
    HANDLE t;
    int number = 1;
    t = CreateThread(NULL, 0, threadHandler, (LPVOID) number, 0, NULL);
    CloseHandle(t);
    number = 2;
    t = CreateThread(NULL, 0, threadHandler, (LPVOID) number, 0, NULL);
    CloseHandle(t);
    if (argc > 1) {
        ExitThread(0);
    } else {
        system("pause");
        return 0;
    }
}

DWORD WINAPI threadHandler(LPVOID param) {
    int number = (int) param;
    while (true) {
        Sleep(1000);
        cout << number;
    }
    return 0;
}
