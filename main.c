#include <stdio.h>
#include "sudoku.h"
#include "sudoku.c"
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

int main() {
    srand((unsigned int)time(NULL));
    // Generating the Sudoku
    int empty_board[9][9] = {0};
    int answer_board[9][9] = {0};
    generate_puzzle(empty_board, answer_board, EXTREME);

    // Main Game Logic
    InitWindow(800, 600, "Hello raylib");

    // The Size of a cell 50x50 pixels.
    int cellWidth = 50;
    int cellHeight = 50;
    int offSetX = 50; // 50 pixels to the right from the top-left corner
    int offSetY = 50; // 50 pixels to the bottom from the top-left corner

    // Vector for line thickness for 3x3 squares
    (Vector2){50.0f, 100.0f};
    // Creating the images for the numbersW

    // Game loop
    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);
        
        // Draw vertical lines
        for(int i = 0; i <= 9; i++) {
            DrawLine(offSetX + i * cellWidth, offSetY, offSetX + i * cellWidth, cellHeight * 10, BLACK);
            if ( i % 3 == 0) {
                DrawLineEx((Vector2){offSetX + i * cellWidth, offSetY}, (Vector2){offSetX + i * cellWidth, cellHeight * 10}, 3.0f, BLACK);
            }
        }
        // Draw horizontal lines
        for(int i = 0; i <= 9; i++) {
            DrawLine(offSetX, offSetY + i * cellHeight, cellHeight * 10 , offSetY + i * cellHeight, BLACK);
            if (i % 3 == 0) {
                DrawLineEx((Vector2){offSetX, offSetY + i * cellHeight}, (Vector2){cellHeight * 10, offSetY + i * cellHeight}, 3.0f, BLACK);
            }
        }
        // Draw the permenant numbers
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if(empty_board[i][j] != 0) {
                    DrawText(TextFormat("%d", empty_board[i][j]), 65 + j*50, 56 + i*50, 40, BLACK);
                }
            }
        }
        // DrawText(TextFormat("%d", empty_board[4][8]),65 + 8*50 ,56, 40, BLACK);
        // DrawText("9",65 + 2*25 ,56, 40, BLACK);
        // DrawText("4",65,56 + 2*25, 40, BLACK);
        // DrawText("9",65 + 2*25,56 + 2*25, 40, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}