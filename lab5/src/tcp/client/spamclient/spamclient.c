#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include <errno.h>

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
    if (argc < 4) {
        printf("usage: spamclient <ip> <port> <message>");
        return 1;
    }
    const char *addr = argv[1];
    int port = atoi(argv[2]);
    const char *message = argv[3];
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
        res = sendFix(sock, message, 0);
        if (res <= 0) {
            perror("Error while sending");
            return 1;
        }
        res = readFix(sock, buf, 100, 0);
        if (res <= 0) {
            fprintf(stderr, "Error while receiving after sending '%s': %s\n", message, strerror(errno));
            return 1;
        }
        sleep(1);
    }
    return 0;
}

