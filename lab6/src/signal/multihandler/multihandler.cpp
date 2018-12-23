#include <windows.h>
#include <iostream>

BOOL CtrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
        case CTRL_C_EVENT:
            printf("Ctrl-C event\n");
            Beep(750, 300);
            SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, FALSE);
            printf("Handler default returned\n");
            return TRUE;
        case CTRL_CLOSE_EVENT:
            Beep(600, 200);
            printf("Ctrl-Close event\n");
            return TRUE;
        case CTRL_BREAK_EVENT:
            Beep(900, 200);
            printf("Ctrl-Break event\n");
            return FALSE;
        case CTRL_LOGOFF_EVENT:
            Beep(1000, 200);
            printf("Ctrl-Logoff event\n");
            return FALSE;
        case CTRL_SHUTDOWN_EVENT:
            Beep(750, 500);
            printf("Ctrl-Shutdown event\n");
            return FALSE;
        default:
            return FALSE;
    }
}

int main(int argc, char *argv[]) {
    if (SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE)) {
        printf("The Control Handler is installed.\n");
        printf("Now try pressing Ctrl+C or Ctrl+Break, or");
        printf("try logging off or closing the console...\n");
        printf("(...waiting in a loop for events...)\n\n");
        while (true);
        return 0;
    } else {
        printf("Error: Could not set control handler: %ld", GetLastError());
        return 1;
    }
}