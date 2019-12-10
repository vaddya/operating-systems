#include <windows.h>
#include <detours.h>
#include <iostream>

int main() 
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);
    
    LPCWSTR app = L"C:\\Git\\operating-systems\\lab9\\src\\CreateFileApp\\Debug\\CreateFileApp.exe";
    LPCSTR dll = "C:\\Git\\operating-systems\\lab9\\src\\HooksLib\\Debug\\HooksLib.dll";
    if (!DetourCreateProcessWithDll(app, NULL, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi, dll, NULL))
    {
        std::cerr << "Error Creating process: " << GetLastError();
        system("pause");
        return -1;
    }

    system("pause");
    return 0;
}
