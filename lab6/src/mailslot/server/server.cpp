#include <windows.h>
#include <iostream>

const int BUF_SIZE = 512;
const char *mailSlotName = R"(\\.\mailslot\MailSlot)";

int main(int argc, char *argv[]) {
    HANDLE mailSlotHandle = CreateMailslot(mailSlotName, 0, MAILSLOT_WAIT_FOREVER, NULL);
    if (mailSlotHandle == INVALID_HANDLE_VALUE) {
        printf("Error: CreateMailSlot, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    printf("Created MailSlot: %s\n", mailSlotName);
    DWORD msgCount;
    DWORD read;
    char buf[BUF_SIZE];
    while (true) {
        if (!GetMailslotInfo(mailSlotHandle, NULL, NULL, &msgCount, NULL)) {
            printf("GetMailSlotInfo error, GetLastError = %ld\n", GetLastError());
            break;
        }
        if (msgCount != 0) {
            if (!ReadFile(mailSlotHandle, buf, 512, &read, NULL)) {
                printf("ReadFile error, GetLastError = %ld!\n", GetLastError());
                break;
            }
            printf("Received %ld bytes: %s", read, buf);
            if (strncmp(buf, "exit", 4) == 0) {
                break;
            }
        }
    }
    CloseHandle(mailSlotHandle);
    return 0;
}
