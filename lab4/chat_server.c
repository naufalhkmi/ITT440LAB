#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    char client_message[2000];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("could not create socket\n");
        return 1;
    }

    int opt = 1;
    setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        return 1;
    }

    listen(socket_desc, 5);
    printf("chat server running on port 8888. waiting for clients...\n");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);
        printf("new client connected: %s:%d\n", client_ip, client_port);

        pid_t pid = fork();
        if (pid == 0) {
            close(socket_desc);
            char welcome[100];
            snprintf(welcome, sizeof(welcome), "welcome to the chat server! type 'bye' to exit.\n");
            send(client_sock, welcome, strlen(welcome), 0);

            int read_size;
            while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
                client_message[read_size] = '\0';
                if (strncmp(client_message, "bye", 3) == 0) {
                    printf("client %s:%d disconnected.\n", client_ip, client_port);
                    break;
                }
                printf("[%s:%d]: %s", client_ip, client_port, client_message);

                char reply[2100];
                snprintf(reply, sizeof(reply), "server echo: %s", client_message);
                send(client_sock, reply, strlen(reply), 0);
            }
            close(client_sock);
            exit(0);
        }
        close(client_sock);
    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}
