#include <windows.h>
#include <iostream>

const int BUF_SIZE = 512;
const char *mailslotTemplate = R"(\\%s\mailslot\MailSlot)";

int main(int argc, char *argv[]) {
    char mailSlotName[BUF_SIZE];
    const char *server;
    if (argc < 2) {
        server = ".";
    } else if (strncmp(argv[1], "all", 3) == 0) {
        server = "*";
    } else {
        server = argv[1];
    }
    sprintf(mailSlotName, mailslotTemplate, server);
    HANDLE mailSlotHandle = CreateFile(mailSlotName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (mailSlotHandle == INVALID_HANDLE_VALUE) {
        printf("CreateFile error, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    printf("Connected to MailSlot: %s\n", mailSlotName);
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    DWORD written;
    while (true) {
        printf("Enter msg to send:\n");
        fgets(buf, BUF_SIZE, stdin);
        if (!WriteFile(mailSlotHandle, buf, strlen(buf) + 1, &written, NULL)) {
            printf("WriteFile error, GetLastError = %ld\n", GetLastError());
            break;
        }
        printf("Sent %ld bytes: %s", written, buf);
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
    }
    CloseHandle(mailSlotHandle);
    return 0;
}
