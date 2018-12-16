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
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(port);
    peer.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket call failed");
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
        ssize_t res = sendto(s, buf, strlen(buf), 0, (struct sockaddr *) &peer, sizeof(peer));
        if (res <= 0) {
            perror("Error while sending");
            return 1;
        }
        bzero(buf, 100);
        struct sockaddr_in from;
        socklen_t from_size;
        recvfrom(s, buf, BUFFER_SIZE, 0, (struct sockaddr *) &from, &from_size);
        if (res <= 0) {
            perror("Error while receiving");
            return 1;
        }
        printf("Server's response: %s\n", buf);
    }
    shutdown(s, SHUT_RDWR);
    close(s);
    return 0;
}
