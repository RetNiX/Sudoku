#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

int main() {
    srand((unsigned int)time(NULL));

    // Generating the Sudoku
    int empty_board[9][9] = {0};
    int answer_board[9][9] = {0}; // For comparing the user's choice
    generate_puzzle(empty_board, answer_board, EXTREME);

    // # ============ Main Game Logic ============ #
    InitWindow(800, 600, "Hello raylib");

    // Vector for line thickness for 3x3 squares
    (Vector2){50.0f, 100.0f};
    // Creating the images for the numbersW

    // Game loop
    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);
        
        // Draw vertical lines
        for(int i = 0; i <= 9; i++) {
            DrawLine(OFFSET + i * CELL_SIZE, OFFSET, OFFSET + i * CELL_SIZE, CELL_SIZE * 10, BLACK);
            if ( i % 3 == 0) {
                DrawLineEx((Vector2){OFFSET + i * CELL_SIZE, OFFSET}, (Vector2){OFFSET + i * CELL_SIZE, CELL_SIZE * 10}, 3.0f, BLACK);
            }
        }
        // Draw horizontal lines
        for(int i = 0; i <= 9; i++) {
            DrawLine(OFFSET, OFFSET + i * CELL_SIZE, CELL_SIZE * 10 , OFFSET + i * CELL_SIZE, BLACK);
            if (i % 3 == 0) {
                DrawLineEx((Vector2){OFFSET, OFFSET + i * CELL_SIZE}, (Vector2){CELL_SIZE * 10, OFFSET + i * CELL_SIZE}, 3.0f, BLACK);
            }
        }
        // Draw the permenant numbers
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if(empty_board[i][j] != 0) {
                    DrawText(TextFormat("%d", empty_board[i][j]), (OFFSET + 15) + j * OFFSET, (OFFSET + 6) + i * OFFSET, 40, BLACK);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}