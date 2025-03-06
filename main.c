//
// Created by srijan on 2/25/25.
//

#include <stdio.h>

#include "3t_game.h"

int main() {
   int board[BOARD_SIZE][BOARD_SIZE] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
   };
   int val = 2;
   display_board(board);
   while (!is_complete(board)) {
      int inp;
      val = (val == 2) ? 1 : 2;
      printf("Enter number 1-9:");
      scanf("%d" , &inp);
      if (inp <= 9 && inp >= 0 && (board[(9-inp)/3][(inp-1)%3] == 0)) {
         board[(9-inp)/3][(inp-1)%3] =  val;
      } else {
         val = (val == 2) ? 1 : 2;
         continue;
      }
      display_board(board);
      if (check_winner(board) != 0) {
         break;
      }
   }
   printf("Winner is: %i\n", check_winner(board));
}
