#include <windows.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "STD INPUT HANDLE = " << GetStdHandle(STD_INPUT_HANDLE) << endl;
    cout << "STD OUTPUT HANDLE = " << GetStdHandle(STD_OUTPUT_HANDLE) << endl;
    char buf[2];
    unsigned long available;
    unsigned long read;
    while (true) {
        PeekNamedPipe(GetStdHandle(STD_INPUT_HANDLE), NULL, NULL, NULL, &available, NULL);
        if (available) {
            memset(buf, '\0', sizeof(buf));
            ReadFile(GetStdHandle(STD_INPUT_HANDLE), buf, 1, &read, NULL);
            cout << buf;
        }
    }
    return 0;
}
