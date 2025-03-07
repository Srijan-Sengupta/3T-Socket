//
// Created by srijan on 2/25/25.
//

#include "client.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#include "3t_game.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <addr> <port>\n", argv[0]);
        exit(1);
    }
    struct sockaddr_in server_addr;
    char buffer[6];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(strtol(argv[2], NULL, 10));
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Address not found");
        exit(1);
    }
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &server_addr, sizeof(server_addr));

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server\n");

    while (strcmp(buffer, "start") != 0) {
        recv(sock, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
    }
    fflush(stdout);
    fflush(stdin);

    recv(sock, buffer, sizeof(buffer), 0);
    signal(SIGINT, INT_quit_handler);
    signal(SIGTERM, INT_quit_handler);
    int board[BOARD_SIZE][BOARD_SIZE] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    const int player = strtol(buffer, NULL, 10);
    int playing = 0, winner = 0;
    int val = 2;
    printf("You are playing as %d\n", player);
    display_board(board);
    while (!is_complete(board)) {
        int inp;
        val = (val == 2) ? 1 : 2;
        if (playing == player) {
            printf("Enter number 1-9: ");
            scanf("%d", &inp);
            sprintf(buffer, "%d", inp);
            if (inp <= 9 && inp >= 0 && (board[(9 - inp) / 3][(inp - 1) % 3] == 0)) {
                send(sock, buffer, sizeof(buffer), 0);
            }
        }else {
            recv(sock, buffer, sizeof(buffer), 0);
            printf("%s\n", buffer);
            if (buffer[0] == 'q') {
                winner = player+1;
                break;
            }
            inp = strtol(buffer, NULL, 10);
        }

        if (inp <= 9 && inp >= 0 && (board[(9 - inp) / 3][(inp - 1) % 3] == 0)) {
            board[(9 - inp) / 3][(inp - 1) % 3] = val;
            playing = !playing;
        } else {
            val = (val == 2) ? 1 : 2;
            continue;
        }
        display_board(board);
        if (check_winner(board) != 0) {
            break;
        }
    }
    winner = (winner)? winner:check_winner(board);
    if (winner == 0) {
        printf("It was a draw!\n");
    }else if (winner == player+1) {
        printf("You won!\n");
    }else {
        printf("You lost!\n");
    }
    close(sock);
}

void  INT_quit_handler(int arg) {
    send(sock,  "quit", 6, 0);
    printf("You lost!");
    close(sock);
    exit(1);
}
