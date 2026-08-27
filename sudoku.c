#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <time.h>


bool is_valid(int board[9][9], int checked_number, int row, int col) {
    // Checking if number exits in row and column
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == checked_number) {
            return false;
        }
        if (board[i][col] == checked_number) {
            return false;
        }
    }
    // Checking if number exits in box 3x3
    // Calculating the top-left corner position from the current row-col
    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int i = start_row; i < start_row + 3; i++) {
        for(int j = start_col; j < start_col + 3; j++) {
            if (board[i][j] == checked_number) {
                return false;
            }
        }
    }
    return true;
}

bool find_empty_cell(int board[9][9], int *row, int *col) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                *row = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}
/* 
 Main idea:
 1. Find an empty slot
 2. Check what number is availble at this cell from 1 to 9.
 3. The first number available, put it in and keep moving to a new empty cell.
 4. repeat until works, if not, backtrack back to the number that didnt work.
 5. Keep going, until everything works.
*/
bool solve(int board[9][9]) {
    int row, col;
    // #1
    if (!find_empty_cell(board, &row, &col)) {
        return true;
    }
    // Creating random array of choice numbers
    int num_range[] = {1,2,3,4,5,6,7,8,9};
    int arr_size = sizeof(num_range) / sizeof(num_range[0]);
    shuffle (num_range, arr_size);

    // #2
    for (int i = 0; i < 9; i++) {
        if (is_valid(board, num_range[i], row, col)) {
            board[row][col] = num_range[i];
            if(solve(board)) {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

void print_board(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("-------------------------------\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                printf("|  ");
            }
            printf("%d  ", board[i][j]);
        }
        printf("\n");
    }
}

void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void punch_holes(int board[9][9], int total_punch_holes) {
    int rand_row, rand_col, curr_punched_holes = 0;
    
    while(curr_punched_holes < total_punch_holes) {
        rand_row = (rand() % 9);
        rand_col = (rand() % 9);
        if (board[rand_row][rand_col] != 0){
            board[rand_row][rand_col] = 0;
            curr_punched_holes++;
        }    
    }
}

void generate_puzzle(int board[9][9], Difficulty choice) {
    /*
        1. Solve the provided board.
        2. Punch holes in the board depending on the difficulty.
        3. Print the board.

        Difficulty punched holes: (At least 17 empty cells should be remaining.)
            EASY = 30 - 39
            MEDIUM = 40 - 49
            HARD = 50 - 57
            EXTREME = 58 - 64
    */
   if (solve(board)) {
        switch(choice) {
            case EASY:
                punch_holes(board, (rand() % 10) + 30);
                break;
            case MEDIUM:
                punch_holes(board, (rand() % 10) + 40);
                break;
            case HARD:
                punch_holes(board, (rand() % 8) + 50);
                break;
            case EXTREME:
                punch_holes(board, (rand() % 7) + 58);
                break;
            default:
                // Default: just make it super easy
                punch_holes(board, (rand() % 10) + 25);
        }
        print_board(board);
   }
}