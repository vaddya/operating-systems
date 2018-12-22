#include <iostream>
#include <winsock2.h>
#include "utils.h"

const int BUF_SIZE = 100;
const int DEF_PORT = 7500;

int main(int argc, char *argv[]) {
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error: %ld\n", GetLastError());
        return 1;
    }
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Server is started\n");
    printf("Try to create socket\n");
    if (server_socket == INVALID_SOCKET) {
        printf("Error with creation socket. GetLasterror = %ld\n", GetLastError());
        return 1;
    }
    int port = DEF_PORT;
    if (argc >= 2) {
        port = atoi(argv[1]);
    }
    struct sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    printf("Try to bind socket\n");
    if (bind(server_socket, (struct sockaddr *) &sin, sizeof(sin)) != 0) {
        printf("Error with bind socket. GetLasterror = %ld\n", GetLastError());
        return 1;
    }
    printf("Try to set socket listening \n");
    if (listen(server_socket, 5) != 0) {
        printf("error with listen socket. GetLasterror= %ld\n", GetLastError());
        return 1;
    }
    printf("Server starts listening at port %d\n", port);
    struct sockaddr_in from{};
    int fromlen = sizeof(from);
    SOCKET client_socket = accept(server_socket, (struct sockaddr *) &from, &fromlen);
    if (client_socket == INVALID_SOCKET) {
        printf("error with accept socket. GetLasterror= %ld\n", GetLastError());
        return 1;
    }
    printf("Get client with IP = %s, port = %d\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
    char buf[BUF_SIZE];
    int readbytes;
    while (true) {
        if ((readbytes = recvLine(client_socket, buf, BUF_SIZE)) == 0) {
            printf("Connection refused\n");
            break;
        } else if (readbytes == -1) {
            printf("buf is small\n");
            return 2000;
        }
        printf("Get msg from client \"%s\" with size= %d\n", buf, readbytes);
        sendLine(client_socket, buf);
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
    }
    closesocket(client_socket);
    closesocket(server_socket);
    return 0;
}
