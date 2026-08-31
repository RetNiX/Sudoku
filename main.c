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
    generate_puzzle(empty_board,EASY);

    // Main Game Logic
    InitWindow(800, 600, "Hello raylib");

    // The Size of a cell 50x50 pixels.
    int cellWidth = 50;
    int cellHeight = 50;
    int offSetX = 50; // 50 pixels to the right from the top-left corner
    int offSetY = 50; // 50 pixels to the bottom from the top-left corner

    // Vector for line thickness for 3x3 squares
    (Vector2){50.0f, 100.0f};
    // Creating the images for the numbers
    const char *imagePaths[10] = {
        "",
        "images/OnePerm.png",
        "images/TwoPerm.png",
        "images/ThreePerm.png",
        "images/FourPerm.png",
        "images/FivePerm.png",
        "images/SixPerm.png",
        "images/SevenPerm.png",
        "images/EightPerm.png",
        "images/NinePerm.png"
        
    };
    Texture2D permNumbers[10];
    // Loading the images of the number to the GPU
    for (int i = 1; i <= 9; i++) {
        permNumbers[i] = LoadTexture(imagePaths[i]);
    }
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
        DrawText("4", 65, 60, 35, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}