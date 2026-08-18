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
    // Checking if number exits in box 3x3
    // Calculating the top-left corner position from the current row-col
    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int i = start_row; i < start_row + 3; i++) {
        for(int j = start_col; j < start_col + 3; j++) {
            if (curr_board[i][j] == checked_number) {
                return false;
            }
        }
    }
    return true;
}