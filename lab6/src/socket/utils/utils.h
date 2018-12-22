#ifndef SRC_UTILS_H
#define SRC_UTILS_H

#include <windows.h>
#include <winsock2.h>

int sendn(SOCKET s, char *buf, int len, int flags);

int recvLine(SOCKET s, char *buf, int len);

int recvn(SOCKET fd, char *buf, size_t len);

int sendLine(SOCKET s, char *buf);

#endif //SRC_UTILS_H
