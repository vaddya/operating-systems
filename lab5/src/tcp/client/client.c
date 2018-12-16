#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DEF_PORT = 8888;
const char *DEF_IP = "127.0.0.1";
const int BUFFER_SIZE = 100;

int readFix(int sock, char *buf, int bufSize, int flags) {
    unsigned msgLength = 0;
    int res = recv(sock, &msgLength, sizeof(unsigned), flags | MSG_WAITALL);
    if (res <= 0) {
        return res;
    }
    if (res > bufSize) {
        printf("Received more data, then we can store, exiting\n");
        exit(1);
    }
    return recv(sock, buf, msgLength, flags | MSG_WAITALL);
}

int sendFix(int sock, char *buf, int flags) {
    unsigned msgLength = strlen(buf);
    int res = send(sock, &msgLength, sizeof(unsigned), flags);
    if (res <= 0) {
        return res;
    }
    return send(sock, buf, msgLength, flags);
}

int main(int argc, char **argv) {
    const char *addr;
    int port;
    if (argc < 3) {
        printf("Using default port %d\n", DEF_PORT);
        port = DEF_PORT;
    } else {
        port = atoi(argv[2]);
    }
    if (argc < 2) {
        printf("Using default addr %s\n", DEF_IP);
        addr = DEF_IP;
    } else {
        addr = argv[1];
    }
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(port);
    peer.sin_addr.s_addr = inet_addr(addr);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Can't create socket\n");
        return 1;
    }
    int res = connect(sock, (struct sockaddr *) &peer, sizeof(peer));
    if (res) {
        perror("Can't connect to server:");
        return 1;
    }
    char buf[BUFFER_SIZE];
    while (1) {
        printf("Input request (empty to exit):\n");
        bzero(buf, BUFFER_SIZE);
        fgets(buf, BUFFER_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';
        if (strlen(buf) == 0) {
            printf("Bye-bye\n");
            break;
        }
        res = sendFix(sock, buf, 0);
        if (res <= 0) {
            perror("Error while sending");
            return 1;
        }
        bzero(buf, 100);
        res = readFix(sock, buf, 100, 0);
        if (res <= 0) {
            perror("Error while receiving");
            return 1;
        }
        printf("Server's response: %s\n", buf);
    }
    return 0;
}
