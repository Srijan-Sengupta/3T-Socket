//
// Created by srijan on 2/25/25.
//

#include "3t_game.h"

#include <stdio.h>
/*
 * 0 - Not Placed
 * 1 - Player 1 played
 * 2 - Player 2 played
 */
// Checks if the the board is filled
int is_complete(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

/*
 * return of check_winner -
 * 0 -> tie
 * 1 -> player 1
 * 2 -. player 2
 */

int check_winner(int board[BOARD_SIZE][BOARD_SIZE]) {
    int winner = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] & board[i][1] & board[i][2]) != 0) {
            winner = board[i][0];
            break;
        }
        if ((board[0][i] & board[1][i] & board[2][i]) != 0) {
            winner = board[0][i];
            break;
        }
    }
    // Check the diagonal
    if ((board[0][0] & board[1][1] & board[2][2]) != 0) {
        winner = board[0][0];
    }
    if ((board[0][2] & board[1][1] & board[2][0]) != 0) {
        winner = board[0][2];
    }
    return winner;
}

void display_board(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("\t___\t\t___\t\t___\n");
        for (int j = 0; j < 3; j++) {
            const char disp = (board[i][j] == 0) ? ' ' : ((board[i][j] == 1) ? 'X' : 'O');
            printf("|\t%c\t|", disp);
        }
        printf("\n");
    }
    printf("\t___\t\t___\t\t___\n");
}
