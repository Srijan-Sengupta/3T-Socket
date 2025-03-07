#include "server.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include<pthread.h>

int main(int argc, char *argv[]) {
    int port;
    if (argc != 2) {
        port = SERVER_PORT;
    } else {
        port = (int) strtoll(argv[1], NULL, 10);
    }
    int clientfd[2] = {};
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(server_addr);

    //CreateSocket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed to create.");
        exit(EXIT_FAILURE);
    }

    //Bind
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed.");
    }

    //Listen
    if (listen(server_fd, 512) == -1) {
        perror("listen failed.");
    }
    printf("Server listening on port %d\n", port);

    signal(SIGINT, INT_handler);
    signal(SIGTERM, INT_handler);

    // Accept cons
    while (1) {
        for (int i = 0; i < 2; i++) {
            clientfd[i] = accept(server_fd, (struct sockaddr *) &server_addr, &addrlen);
            if (clientfd[i] == -1) {
                perror("accept failed.");
                i--;
                continue;
            }
            int one = 1;
            setsockopt(clientfd[i], IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
            send(clientfd[i], "wait", 4, 0);
            printf("Client %d connected\n", i);
        }
        int *arr = malloc(sizeof(int) * 2);
        memcpy(arr, clientfd, sizeof(clientfd));

        pthread_t thread;
        pthread_create(&thread, NULL, replicate, arr);
        pthread_detach(thread);
    }


    /*strcpy(buffer, "start");
    for (int i = 0; i < 2; i++)
        send(clientfd[i], buffer, 6, 0);

    for (int i = 0; i < 2; i++) {
        sprintf(buffer, "%d", i);
        send(clientfd[i], buffer, 4, 0);
    }
    int player = 0;
    while (recv(clientfd[player], &buffer, 6, 0)) {
        send(clientfd[!player], buffer, 6, 0);
        player = !player;
    }
    close(clientfd[0]);
    close(clientfd[1]);
    close(server_fd);*/
}

void *replicate(void *clients) {
    int *clientfd = (int *) clients;
    char buffer[6] = {};
    strcpy(buffer, "start");
    for (int i = 0; i < 2; i++)
        send(clientfd[i], buffer, sizeof(buffer), 0);

    for (int i = 0; i < 2; i++) {
        sprintf(buffer, "%d", i);
        send(clientfd[i], buffer, sizeof(buffer), 0);
    }
    int player = 0;
    while (recv(clientfd[player], &buffer, sizeof(buffer), 0)) {
        send(clientfd[!player], buffer, sizeof(buffer), 0);
        player = !player;
    }
    close(clientfd[0]);
    close(clientfd[1]);
    free(clientfd);
    return 0;
}

void INT_handler(int) {
    printf("Shutting down gracefully");
    close(server_fd);
    exit(0);
}
