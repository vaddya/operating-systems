#include <windows.h>
#include <iostream>

const int BUF_SIZE = 256;
TCHAR szName[] = TEXT("MyFileMappingObject");
TCHAR szMsg[] = TEXT("Message from first process");
HANDLE mutex;

int main(int argc, char *argv[]) {
    HANDLE mapFile;
    LPCTSTR pBuf;
    mutex = CreateMutex(NULL, false, TEXT("SyncMutex"));
    mapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, szName);
    if (mapFile == NULL || mapFile == INVALID_HANDLE_VALUE) {
        printf("Cannot create file mapping. GetLastError = %ld\n", GetLastError());
        return 1;
    }
    pBuf = (LPTSTR) MapViewOfFile(mapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        printf("Cannot map view of file. GetLastError = %ld\n", GetLastError());
        return 1;
    }
    int i = 0;
    while (true) {
        i = rand();
        itoa(i, (char *) szMsg, 10);
        WaitForSingleObject(mutex, INFINITE);
        CopyMemory((PVOID) pBuf, szMsg, sizeof(szMsg));
        printf("Write message: %s\n", (char *) pBuf);
        Sleep(1000);
        ReleaseMutex(mutex);
    }
    UnmapViewOfFile(pBuf);
    CloseHandle(mapFile);
    CloseHandle(mutex);
}
