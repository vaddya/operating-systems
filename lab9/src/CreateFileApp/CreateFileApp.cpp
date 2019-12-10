#include <Windows.h>
#include <iostream>

int main()
{
    HANDLE WINAPI handle = CreateFile(L"C:\\Test\\file.txt", GENERIC_ALL, FILE_SHARE_READ,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    std::cout << "handle=" << handle << std::endl;

    char bytes[] = { 'h', 'e', 'l', 'l', 'o' };
    WriteFile(handle, bytes, 5, 0, nullptr);

    return 0;
}
