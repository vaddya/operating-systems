#include <windows.h>
#include <iostream>

const int BUF_SIZE = 256;
const int TIME = 15;
TCHAR szName[] = TEXT("MyFileMappingObject");
HANDLE mutex;

int main(int argc, char *argv[]) {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("SyncMutex"));
    if (mutex == NULL) {
        printf("OpenMutex error: %ld\n", GetLastError());
        return 1;
    }
    printf("OpenMutex successfully opened the mutex.\n");
    hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szName);
    if (hMapFile == NULL) {
        printf("Cannot open file mapping. GetLastError = %ld\n", GetLastError());
        return 1;
    }
    pBuf = (LPTSTR) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        printf("Cannot map view of file. GetLastError = %ld\n", GetLastError());
        return 1;
    }
    for (int i = 0; i < TIME; i++) {
        WaitForSingleObject(mutex, INFINITE);
        printf("Read message: %s\n", (char *) pBuf);
        ReleaseMutex(mutex);
    }
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}
