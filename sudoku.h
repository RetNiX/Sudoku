#pragma once // Safegaurding for the typedef problem

#include <stdbool.h>

// Making the difficulties as a type.
typedef enum {
    EASY,
    MEDIUM,
    HARD,
    EXTREME
} Difficulty;

// Checking if a number is valid to put in the cell, according to the sudoku rules.
bool is_valid(int board[9][9], int checked_number, int row, int col);

// Find an empty cell.
bool find_empty_cell(int board[9][9], int *row, int *col);

// Main solver function. Using backtracking algorithm
bool solve(int board[9][9]);

// Print Board
void print_board(int board[9][9]);

// Shuffle algorith for sudoku generator
void shuffle(int arr[], int size);

// Punch holes into a solved sudoku
void punch_holes(int board[9][9], int total_punch_holes);

// Main Sudoku Generating Function
void generate_puzzle(int generated_board[9][9], int solved_baord[9][9], Difficulty choice);