#include <iostream>
#include <winsock2.h>
#include <vector>
#include "utils.h"

const int BUF_SIZE = 100;
const int DEF_PORT = 7500;

std::vector<SOCKET> sockets{};
HANDLE mutex;

DWORD WINAPI threadHandler(LPVOID param) {
    SOCKET clientSocket = (SOCKET) param;
    char buf[BUF_SIZE];
    int readbytes;
    while (true) {
        memset(buf, 0, BUF_SIZE);
        if ((readbytes = recvLine(clientSocket, buf, BUF_SIZE)) == 0) {
            printf("Connection refused\n");
            break;
        } else if (readbytes == -1) {
            printf("Reading error\n");
            WaitForSingleObject(mutex, INFINITE);
            for (auto it = sockets.begin(); it != sockets.end(); it++) {
                if (*it == clientSocket) {
                    sockets.erase(it);
                    break;
                }
            }
            ReleaseMutex(mutex);
            break;
        }
        printf("Got msg from client %d: \"%s\" with size = %d\n", clientSocket, buf, readbytes);
        printf("Enter answer to client:\n");
        fgets(buf, BUF_SIZE, stdin);
        sendLine(clientSocket, buf);
    }
    closesocket(clientSocket);
    WaitForSingleObject(mutex, INFINITE);
    for (auto it = sockets.begin(); it != sockets.end(); it++) {
        if (*it == clientSocket) {
            sockets.erase(it);
            break;
        }
    }
    ReleaseMutex(mutex);
    return 0;
}

int main(int argc, char *argv[]) {
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error: %ld\n", GetLastError());
        return 1;
    }
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        printf("Error with CreateMutex: %ld\n", GetLastError());
        return 1;
    }
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
    printf("Try to set socket listening\n");
    if (listen(serverSocket, 5) != 0) {
        printf("Error with listen socket. GetLasterror= %ld\n", GetLastError());
        return 1;
    }
    printf("Server starts listening at port %d\n", port);
    sockaddr_in from{};
    int fromlen = sizeof(from);
    while (true) {
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr *) &from, &fromlen);
        if (clientSocket == INVALID_SOCKET) {
            printf("Error with accept socket. GetLasterror = %ld\n", GetLastError());
            return 1;
        }
        printf("Get client with IP = %s, port = %d\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
        WaitForSingleObject(mutex, INFINITE);
        HANDLE t = CreateThread(NULL, 0, threadHandler, (LPVOID) clientSocket, 0, NULL);
        sockets.push_back(clientSocket);
        printf("List of clients sockets:\n");
        for (auto socket : sockets) {
            printf("- %d\n", socket);
        }
        ReleaseMutex(mutex);
        CloseHandle(t);
    }
    closesocket(serverSocket);
    return 0;
}
