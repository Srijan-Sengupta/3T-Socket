//
// Created by srijan on 2/25/25.
//

#ifndef INC_3T_GAME_H
#define INC_3T_GAME_H
#ifndef BOARD_SIZE
#define BOARD_SIZE 3
#endif

int is_complete(int board[BOARD_SIZE][BOARD_SIZE]);
int check_winner(int board[BOARD_SIZE][BOARD_SIZE]);
void display_board(int board[BOARD_SIZE][BOARD_SIZE]);

#endif //INC_3T_GAME_H
