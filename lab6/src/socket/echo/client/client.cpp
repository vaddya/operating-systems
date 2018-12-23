#include <iostream>
#include "utils.h"

const int BUF_SIZE = 100;
const char *DEF_ADDR = "127.0.0.1";
const int DEF_PORT = 7500;

int main(int argc, char *argv[]) {
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error: %ld\n", GetLastError());
        return 1;
    }
    printf("Client is started\n");
    printf("Try to create socket\n");
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created successfully\n");
    const char *addr = DEF_ADDR;
    int port = DEF_PORT;
    if (argc >= 3) {
        addr = argv[1];
        port = atoi(argv[2]);
    }
    sockaddr_in sin{};
    sin.sin_addr.s_addr = inet_addr(addr);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    printf("Try to connect to server: %s:%d\n", addr, port);
    if (connect(client_socket, (struct sockaddr *) &sin, sizeof(sin)) != 0) {
        printf("Connect failed with error: %ld\n", GetLastError());
        return 1;
    }
    printf("Client connected successfully\n");
    char buf[BUF_SIZE];
    while (true) {
        printf("Enter msg to send:\n");
        memset(buf, 0, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        printf("Client sent msg: %s", buf);
        sendLine(client_socket, buf);
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
        memset(buf, 0, BUF_SIZE);
        recvLine(client_socket, buf, BUF_SIZE);
        printf("Got reply from server: \"%s\"\n", buf);
    }
    closesocket(client_socket);
    return 0;
}
