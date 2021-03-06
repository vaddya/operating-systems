#include "utils.h"

const int BUF_SIZE = 100;

int sendn(SOCKET s, char *buf, int len, int flags) {
    int sent = 0;
    int n = -1;
    while (sent < len) {
        n = send(s, buf + sent, len - sent, flags);
        if (n < 0) {
            break;
        }
        sent += n;
    }
    return (n == -1 ? -1 : sent);
}

int recvLine(SOCKET s, char *buf, int len) {
    char *buff = buf;
    char *currPosPointer;
    int count = 0;
    char tempBuf[BUF_SIZE];
    char currChar;
    int tmpcount = 0;
    while (--len > 0) {
        if (--count <= 0) {
            recvn(s, tempBuf, tmpcount);
            count = recv(s, tempBuf, sizeof(tempBuf), MSG_PEEK);
            if (count <= 0) {
                return count;
            }
            currPosPointer = tempBuf;
            tmpcount = count;
        }
        currChar = *currPosPointer++;
        *buf++ = currChar;
        if (currChar == '\n') {
            *(buf - 1) = '\0';
            recvn(s, tempBuf, tmpcount - count + 1);
            return buf - buff - 1;
        }
    }
    return -1;
}

int recvn(SOCKET fd, char *buf, size_t len) {
    return recv(fd, buf, len, 0x8);
}

int sendLine(SOCKET s, char *buf) {
    char tempBuf[BUF_SIZE];
    strcpy(tempBuf, buf);
    if (tempBuf[strlen(tempBuf) - 1] != '\n') {
        strcat(tempBuf, "\n");
    }
    return sendn(s, tempBuf, strlen(tempBuf), 0);
}
