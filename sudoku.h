#include <stdbool.h>

// Checking if a number is valid to put in the cell, according to the sudoku rules
bool is_valid(int board[9][9], int checked_number, int row, int col);

// Find an empty cell
bool find_empty_cell(int board[9][9], int *row, int *col);