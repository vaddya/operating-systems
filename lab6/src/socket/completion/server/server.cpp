#include <winsock2.h>
#include <iostream>
#include <vector>

const int BUF_SIZE = 128;
const int DEF_PORT = 7500;
const int WORKERS_NUM = 5;

std::vector<SOCKET> sockets{};
HANDLE mutex;

struct ovpConnection : public OVERLAPPED {
    int client_number;          // Client number
    SOCKET sock_handle;         // Client socket
    char *buffer;               // Message buffer
    enum {
        op_type_send,           // Sending
        op_type_recv            // Receiving
    } op_type;                  // Operation type
};

void disconnectClient(ovpConnection *conn) {
    printf("Client %d disconnected\n", conn->client_number);
    WaitForSingleObject(mutex, INFINITE);
    for (auto it = sockets.begin(); it != sockets.end(); it++) {
        if (*it == conn->sock_handle) {
            closesocket(conn->sock_handle);
            sockets.erase(it);
            break;
        }
    }
    ReleaseMutex(mutex);
}

DWORD WINAPI poolThread(HANDLE port) {
    DWORD bytes, key, flags;
    char buf[BUF_SIZE];
    LPOVERLAPPED overlapped;
    while (true) {
        memset(buf, 0, BUF_SIZE);
        if (!GetQueuedCompletionStatus(port, &bytes, &key, &overlapped, INFINITE)) {
            if (overlapped == NULL) {
                WaitForSingleObject(mutex, INFINITE);
                for (auto socket : sockets) {
                    closesocket(socket);
                }
                sockets.clear();
                ReleaseMutex(mutex);
                CloseHandle(port);
                printf("Port error, server is shutting down, GetLastError = %ld\n", GetLastError());
                TerminateProcess(GetCurrentProcess(), 1);
            }
            disconnectClient((ovpConnection *) overlapped);
            break;
        }
        auto conn = (ovpConnection *) overlapped;
        switch (conn->op_type) {
            case ovpConnection::op_type_send:
                delete[] conn->buffer;
                delete conn;
                break;
            case ovpConnection::op_type_recv:
                if (bytes == 0) {
                    disconnectClient(conn);
                    break;
                }
                printf("Got msg from client %d: %s", conn->client_number, conn->buffer);
                if (strncmp(conn->buffer, "exit", 4) == 0) {
                    disconnectClient(conn);
                    break;
                }
                if (send(conn->sock_handle, conn->buffer, bytes, 0) < 0) {
                    printf("Error on sending, WSAGetLastError = %d\n", WSAGetLastError());
                }
                WSABUF wsabuf;
                wsabuf.buf = conn->buffer;
                wsabuf.len = BUF_SIZE;
                bytes = flags = 0;
                if (!WSARecv(conn->sock_handle, &wsabuf, 1, &bytes, &flags, conn, NULL)) {
                    printf("Error on WSARecv, WSAGetLastError = %d\n", WSAGetLastError());
                    break;
                }
                memset(conn->buffer, 0, BUF_SIZE);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    WSADATA WSStartData;
    if (WSAStartup(MAKEWORD(2, 0), &WSStartData) != 0) {
        printf("WSAStartup failed with error, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        printf("Error with CreateMutex, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error on WSASocket, WSAGetLastError = %d\n", WSAGetLastError());
        return 1;
    }
    HANDLE completionPort = CreateIoCompletionPort((HANDLE) serverSocket, NULL, 0, 0);
    if (completionPort == NULL) {
        printf("Error on CreateIoCompletionPort, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    int port = DEF_PORT;
    if (argc >= 2) {
        port = atoi(argv[1]);
    }
    sockaddr_in sinServer{};
    memset(&sinServer, 0, sizeof(sinServer));
    sinServer.sin_family = AF_INET;
    sinServer.sin_port = htons(port);
    sinServer.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (LPSOCKADDR) &sinServer, sizeof(sinServer)) < 0) {
        printf("Error on bind, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    if (listen(serverSocket, SOMAXCONN) < 0) {
        printf("Error on listen, GetLastError = %ld\n", GetLastError());
        return 1;
    }
    for (int i = 0; i < WORKERS_NUM; i++) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) poolThread, completionPort, 0, NULL);
    }
    int clientCount = 0;
    printf("Server is started successfully\n");
    DWORD flags, bytes;
    while (true) {
        sockaddr_in sinClient{};
        int lenClient = sizeof(sinClient);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr *) &sinClient, &lenClient);
        CreateIoCompletionPort((HANDLE) clientSocket, completionPort, 0, 0);
        WaitForSingleObject(mutex, INFINITE);
        sockets.push_back(clientSocket);
        printf("List of clients sockets:\n");
        for (auto socket : sockets) {
            printf("- %d\n", socket);
        }
        ReleaseMutex(mutex);
        auto conn = new ovpConnection;
        conn->sock_handle = clientSocket;
        conn->op_type = ovpConnection::op_type_recv;
        conn->buffer = new char[BUF_SIZE];
        memset(conn->buffer, 0, BUF_SIZE);
        conn->hEvent = NULL;
        conn->client_number = ++clientCount;
        printf("Client %d connected\n", clientCount);
        WSABUF wsabuf;
        wsabuf.buf = conn->buffer;
        wsabuf.len = BUF_SIZE;
        bytes = flags = 0;
        if (!WSARecv(conn->sock_handle, &wsabuf, 1, &bytes, &flags, conn, NULL)) {
            printf("Error on WSARecv, WSAGetLastError = %d\n", WSAGetLastError());
        }
    }
    return 0;
}
