#include <iostream>
#include <cassert>
#include "utils.h"

const int BUF_SIZE = 100;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: spam_client.exe <ip> <port> <message>");
        return 1;
    }
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error: %ld\n", GetLastError());
        return 1;
    }
    printf("Client is started\n");
    printf("Try to create socket\n");
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created successfully\n");
    sockaddr_in sin{};
    const char *addr = argv[1];
    int port = atoi(argv[2]);
    sin.sin_addr.s_addr = inet_addr(addr);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    printf("Try to connect to server: %s:%d\n", addr, port);
    if (connect(client_socket, (struct sockaddr *) &sin, sizeof(sin)) != 0) {
        fprintf(stderr, "Connect failed with error: %ld\n", GetLastError());
        return 1;
    }
    printf("Client connected successfully\n");
    char buf[BUF_SIZE];
    char *msg = argv[3];
    printf("Client will send msg: %s\n", msg);
    while (true) {
        sendLine(client_socket, msg);
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
        memset(buf, 0, BUF_SIZE);
        recvLine(client_socket, buf, BUF_SIZE);
        printf("Got reply from server: \"%s\"\n", buf);
        assert(strcmp(buf, msg) == 0);
        Sleep(1000);
    }
    closesocket(client_socket);
    return 0;
}
