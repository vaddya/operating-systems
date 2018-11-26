#include <windows.h>
#include <stdio.h>

#define MESSAGE "It is child process!"

int main(int argc, char *argv[])
{
	printf("It is child process!\n");
	if (argc != 2) {
		printf("Error! File handle must be in args!\n");
		getchar();
		return 1;
	}

	HANDLE hFile = (HANDLE)atoi(argv[1]);
	printf("file handle: %d\n", hFile);
	DWORD nWritten;
	int len = sizeof(MESSAGE) - 1;
	WriteFile(hFile, MESSAGE, len, &nWritten, NULL);
	if (nWritten != len) {
		printf("Write error: %d\n", GetLastError());
		CloseHandle(hFile);
		getchar();
		return 2;
	}
	getchar();
	CloseHandle(hFile);
	return 0;
}