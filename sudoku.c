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