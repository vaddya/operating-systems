#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

const int DEF_PORT = 8888;
const int BUFFER_SIZE = 100;

int readFix(int sock, char *buf, int bufSize, int flags) {
    unsigned msgLength = 0;
    int res = recv(sock, &msgLength, sizeof(unsigned), flags | MSG_WAITALL);
    if (res <= 0) {
        return res;
    }
    if (res > bufSize) {
        printf("Recieved more data, then we can store, exiting\n");
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

void *clientHandler(void *args) {
    int socket = (int) args;
    char buf[BUFFER_SIZE];
    int res = 0;
    while (1) {
        bzero(buf, BUFFER_SIZE);
        res = readFix(socket, buf, BUFFER_SIZE, 0);
        if (res <= 0) {
            perror("Can't recv data from client, ending thread");
            pthread_exit(NULL);
        }
        printf("Some client sent: %s\n", buf);
        res = sendFix(socket, buf, 0);
        if (res <= 0) {
            perror("send call failed");
            pthread_exit(NULL);
        }
    }
}

int main(int argc, char **argv) {
    int port;
    if (argc < 2) {
        printf("Using default port %d\n", DEF_PORT);
        port = DEF_PORT;
    } else {
        port = atoi(argv[1]);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        perror("Can't create socket to listen: ");
        return 1;
    }
    int enable = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    int res = bind(listener, (struct sockaddr *) &addr, sizeof(addr));
    if (res < 0) {
        perror("Can't bind socket");
        return 1;
    }
    res = listen(listener, 5);
    if (res) {
        perror("Error while listening:");
        return 1;
    }
    int counter = 0;
    while (1) {
        int client = accept(listener, NULL, NULL);
        pthread_t thrd;
        res = pthread_create(&thrd, NULL, clientHandler, (void *) (client));
        if (res) {
            fprintf(stderr, "Error while creating new thread: %s, counter = %d", strerror(errno), counter);
            return 1;
        }
        counter++;
    }
    return 0;
}
