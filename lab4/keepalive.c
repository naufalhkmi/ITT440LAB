#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int socket_desc;
    int optval;
    socklen_t optlen = sizeof(optval);

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("could not create socket\n");
        return 1;
    }

    if (getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
        perror("getsockopt");
        close(socket_desc);
        exit(1);
    }
    printf("so_keepalive is %s\n", (optval ? "on" : "off"));

    optval = 1;
    optlen = sizeof(optval);
    if (setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
        perror("setsockopt");
        close(socket_desc);
        exit(1);
    }

    if (getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
        perror("getsockopt");
        close(socket_desc);
        exit(1);
    }
    printf("so_keepalive is %s\n", (optval ? "on" : "off"));

    close(socket_desc);
    return 0;
}
