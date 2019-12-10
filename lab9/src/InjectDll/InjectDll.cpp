#include <windows.h>
#include <detours.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: ./InjectDll PATH_TO_APP PATH_TO_DLL" << std::endl;
        return 1;
    }

    LPCSTR app = argv[1];
    LPCSTR dll = argv[2];

    STARTUPINFOA si = { 0 };
    si.cb = sizeof(STARTUPINFOA);
    PROCESS_INFORMATION pi = { 0 };
    if (!DetourCreateProcessWithDllA(app, NULL, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi, dll, NULL)) {
        std::cerr << "Error creating process: " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    std::cout << "Process created, PID: " << pi.dwProcessId << std::endl;

    return 0;
}
