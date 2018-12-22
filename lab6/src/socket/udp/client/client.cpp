#include <iostream>
#include <winsock2.h>

const int BUF_SIZE = 100;
const char *DEF_ADDR = "127.0.0.1";
const int DEF_PORT = 7500;

int main(int argc, char *argv[]) {
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error: %ld\n", GetLastError());
        return 1;
    }
    printf("Client is started.\n");
    printf("Try to create socket\n");
    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket created successfully\n");
    const char *addr = DEF_ADDR;
    int port = DEF_PORT;
    if (argc >= 3) {
        addr = argv[1];
        port = atoi(argv[2]);
    }
    struct sockaddr_in sin{};
    sin.sin_addr.s_addr = inet_addr(addr);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    printf("Will send messages to server: %s:%d\n", addr, port);
    char buf[BUF_SIZE];
    int sinlen = sizeof(sin);
    while (true) {
        printf("Enter msg to send:\n");
        fgets(buf, BUF_SIZE, stdin);
        printf("Client sent msg: %s", buf);
        sendto(clientSocket, buf, strlen(buf), 0, (struct sockaddr *) &sin, sinlen);
        memset(buf, 0, BUF_SIZE);
        recvfrom(clientSocket, buf, BUF_SIZE, 0, (struct sockaddr *) &sin, &sinlen);
        printf("Got reply from server: %s", buf);
    }
    closesocket(clientSocket);
    return 0;
}
