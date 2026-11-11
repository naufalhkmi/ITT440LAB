
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char *message;
    char client_message[2000];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("could not create socket\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    listen(socket_desc, 3);
    puts("waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        puts("connection accepted");

        message = "hello client, i received your connection.\n";
        write(new_socket, message, strlen(message));

        int read_size = recv(new_socket, client_message, 2000, 0);
        if (read_size > 0) {
            client_message[read_size] = '\0';
            printf("client says: %s\n", client_message);
        }

        close(new_socket);
        puts("waiting for incoming connections...");
    }

    if (new_socket < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}
