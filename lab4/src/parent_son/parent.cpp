#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define CHILD_PROCESS_PATH "C:\\OS\\lab5\\son\\debug\\son.exe"
#define MESSAGE "It is parent process!"

int main(int argc, char *argv[])
{
	printf("in main process\n");

	// ????????? ????, ???????????? ?????????? ?? ???????????? ??????????? ???????????
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	std::wstring wFile= L"file.txt";
	HANDLE hFile = CreateFile(wFile.c_str(), GENERIC_WRITE, 0, &sa, OPEN_ALWAYS, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Create file error: %d\n", GetLastError());
		system("pause");
		return 2;
	}

	char buf[300];
	printf("Handle: %d\n", hFile);
	sprintf(buf, "%s %d", CHILD_PROCESS_PATH, (int)hFile);
	wchar_t wCom[300];
	mbstowcs(wCom, buf, strlen(buf));

	// ????? ? ????
	DWORD nWritten;
	int len = sizeof(MESSAGE) - 1;
	WriteFile(hFile, MESSAGE, len, &nWritten, NULL);
	if (nWritten != len) {
		printf("Write error: %d\n", GetLastError());
		system("pause");
		return 2;
	}
	// ??????? ???????? ???????
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	PROCESS_INFORMATION processInfo;
	if (!CreateProcess(NULL, wCom, NULL, NULL, TRUE,        // ????????? ???????????? ???????????? 
		CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo)) {
		printf("Can't create process: %d\n", GetLastError());
		system("pause");
		return 1;
	}
	Sleep(500);
	// ????? ? ????
	WriteFile(hFile, MESSAGE, len, &nWritten, NULL);
	if (nWritten != len) {
		printf("Write error: %d\n", GetLastError());
		system("pause");
		return 2;
	}

	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
	CloseHandle(hFile);
	system("pause");
	return 0;
}