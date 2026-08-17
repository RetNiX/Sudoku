#include <stdio.h>
#include "sudoku.h"

bool is_valid(int curr_board[9][9], int checked_number, int row, int col) {
    // Checking if number exits in row and column
    for (int i = 0; i < 9; i++) {
        if (curr_board[row][i] == checked_number) {
            return false;
        }
        if (curr_board[i][col] == checked_number) {
            return false;
        }
    }
}