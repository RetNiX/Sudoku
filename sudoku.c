#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

bool find_empty_cell(int board[GRID_SIZE][GRID_SIZE], int *row, int *col) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
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
 2. Choose a random number between 1-9
 3. The first number available, put it in and keep moving to a new empty cell. Update the corresponding bit of the used number.
 4. Repeat until works, if not, backtrack back to the number that didnt work.
 5. Keep going, until everything works.
*/
bool solve(int board[GRID_SIZE][GRID_SIZE], int row_mask[], int col_mask[], int box_mask[]) {
    int row, col;
    // #1
    if (!find_empty_cell(board, &row, &col)) {
        return true;
    }
    // #2
    // Creating random array of choice numbers
    int num_range[] = {1,2,3,4,5,6,7,8,9};
    int arr_size = sizeof(num_range) / sizeof(num_range[0]);
    shuffle (num_range, arr_size);

    // #3-5
    for (int i = 0; i < GRID_SIZE; i++) {
        int curr_num = num_range[i];
        // Calculate the combined mask
        int box_index = (row / 3) * 3 + (col / 3);
        int combined_mask = row_mask[row] | col_mask[col] | box_mask[box_index];
        // Check if the number is availabe (if this bit is a 0)
        if (!(combined_mask & (1 << curr_num))) {
            // Place number and update mask
            board[row][col] = curr_num;
            row_mask[row] |= (1 << curr_num);
            col_mask[col] |= (1 << curr_num);
            box_mask[box_index] |= (1 << curr_num);
            if(solve(board, row_mask, col_mask, box_mask)) {
                return true;
            }
            // Backtrack and clear the masks
            board[row][col] = 0;
            row_mask[row] &= ~(1 << curr_num);
            col_mask[col] &= ~(1 << curr_num);
            box_mask[box_index] &= ~(1 << curr_num);

        }
    }
    return false;
}

void print_board(int board[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("-------------------------------\n");
        }
        for (int j = 0; j < GRID_SIZE; j++) {
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

void punch_holes(int board[GRID_SIZE][GRID_SIZE], int total_punch_holes) {
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

void generate_puzzle(int generated_board[GRID_SIZE][GRID_SIZE], int solved_board[GRID_SIZE][GRID_SIZE], Difficulty choice) {
    /*
        1. Solve the provided board.
        2. Save the solved board for reference and later features.
        3. Punch holes in the board depending on the difficulty.
        4. Print the board.

        Difficulty punched holes: (At least 17 empty cells should be remaining.)
            EASY = 30 - 39
            MEDIUM = 40 - 49
            HARD = 50 - 57
            EXTREME = 58 - 64
    */
   // Initialize the bit masking 
    int row_mask[GRID_SIZE] = {0};
    int col_mask[GRID_SIZE] = {0};
    int box_mask[GRID_SIZE] = {0};
   if (solve(generated_board, row_mask, col_mask, box_mask)) {
        // Save the solved matrix to know the user's guesses
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                solved_board[i][j] = generated_board[i][j];
            }
        }
        switch(choice) {
            case EASY:
                punch_holes(generated_board, (rand() % 10) + 30);
                break;
            case MEDIUM:
                punch_holes(generated_board, (rand() % 10) + 40);
                break;
            case HARD:
                punch_holes(generated_board, (rand() % 8) + 50);
                break;
            case EXTREME:
                punch_holes(generated_board, (rand() % 7) + 58);
                break;
            default:
                // Default: just make it super easy
                punch_holes(generated_board, (rand() % 10) + 25);
        }
        print_board(generated_board);
   }
}