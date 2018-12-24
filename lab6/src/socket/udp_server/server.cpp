#include <iostream>
#include <winsock2.h>

const int BUF_SIZE = 100;
const int DEF_PORT = 7500;

int main(int argc, char *argv[]) {
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error: %ld\n", GetLastError());
        return 1;
    }
    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Server is started\n");
    printf("Try to create socket\n");
    if (serverSocket == INVALID_SOCKET) {
        printf("Error with creation socket. GetLasterror = %ld\n", GetLastError());
        return 1;
    }
    int port = DEF_PORT;
    if (argc >= 2) {
        port = atoi(argv[1]);
    }
    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    printf("Try to bind socket\n");
    if (bind(serverSocket, (struct sockaddr *) &sin, sizeof(sin)) != 0) {
        printf("Error with bind socket. GetLasterror = %ld\n", GetLastError());
        return 1;
    }
    printf("Server starts at port %d\n", port);
    char buf[BUF_SIZE];
    int readbytes;
    sockaddr_in from{};
    int fromlen = sizeof(from);
    while (true) {
        memset(buf, 0, BUF_SIZE);
        readbytes = recvfrom(serverSocket, buf, BUF_SIZE, 0, (struct sockaddr *) &from, &fromlen);
        printf("Got msg from client with IP = %s, port = %d, size = %d\n",
               inet_ntoa(from.sin_addr), ntohs(from.sin_port), readbytes);
        printf("\"%s\"", buf);
        sendto(serverSocket, buf, strlen(buf), 0, (struct sockaddr *) &from, fromlen);
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
    }
    closesocket(serverSocket);
    return 0;
}
