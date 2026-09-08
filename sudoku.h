#pragma once // Safegaurding for the typedef problem

#include <stdbool.h>

#define GRID_SIZE 9
#define CELL_SIZE 50
#define OFFSET 50
// Making the difficulties as a type.
typedef enum {
    EASY,
    MEDIUM,
    HARD,
    EXTREME
} Difficulty;

// Find an empty cell.
bool find_empty_cell(int board[GRID_SIZE][GRID_SIZE], int *row, int *col);

// Main solver function. Using backtracking algorithm
bool solve(int board[GRID_SIZE][GRID_SIZE], int row_mask[], int col_mask[], int box_mask[]);

// Print Board
void print_board(int board[GRID_SIZE][GRID_SIZE]);

// Shuffle algorith for sudoku generator
void shuffle(int arr[], int size);

// Punch holes into a solved sudoku
void punch_holes(int board[GRID_SIZE][GRID_SIZE], int total_punch_holes);

// Main Sudoku Generating Function
void generate_puzzle(int generated_board[GRID_SIZE][GRID_SIZE], int solved_baord[GRID_SIZE][GRID_SIZE], Difficulty choice);

// Check if user's choice is valid without hint
bool check_user_choice(int board[GRID_SIZE][GRID_SIZE], int user_board[GRID_SIZE][GRID_SIZE], int row, int col);