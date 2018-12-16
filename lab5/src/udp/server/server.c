#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int DEF_PORT = 8888;
const int BUFFER_SIZE = 65507;

int main(int argc, char **argv) {
    int port;
    if (argc < 2) {
        printf("Using default port %d\n", DEF_PORT);
        port = DEF_PORT;
    } else {
        port = atoi(argv[1]);
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket call failed");
        return 1;
    }
    int enable = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    int rc = bind(s, (struct sockaddr *) &local, sizeof(local));
    if (rc < 0) {
        perror("bind call failure");
        return 1;
    }
    char buffer[BUFFER_SIZE];
    while (1) {
        bzero(buffer, BUFFER_SIZE);
        struct sockaddr_in from;
        socklen_t from_size = sizeof(from);
        recvfrom(s, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &from, &from_size);
        printf("Server received from port = %d: %s\n", from.sin_port, buffer);
        sendto(s, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &from, from_size);
    }
    shutdown(s, SHUT_RDWR);
    close(s);
    return 0;
}
