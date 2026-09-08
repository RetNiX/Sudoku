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
    int user_board[9][9] = {0}; // User's typed numbers
    generate_puzzle(empty_board, answer_board, EXTREME);

    // # ============ Main Game Logic ============ #
    InitWindow(800, 600, "Hello raylib");

    // Vector for line thickness for 3x3 squares
    (Vector2){50.0f, 100.0f};

    int selected_cell[2] ={-2,-2};
    // int check = GetKeyPressed();
    // printf(" The delete ascii: %d", check);
    // Game loop
    while(!WindowShouldClose()) {
        int key_pressed = GetKeyPressed();
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
        
        DrawRectangle(OFFSET + CELL_SIZE * selected_cell[1], OFFSET + CELL_SIZE * selected_cell[0],CELL_SIZE - 1, CELL_SIZE - 1, SKYBLUE);

        // Draw the permenant numbers
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if(empty_board[i][j] != 0) {
                    DrawText(TextFormat("%d", empty_board[i][j]), (OFFSET + 15) + j * OFFSET, (OFFSET + 6) + i * OFFSET, 40, BLACK);
                }
                if (user_board[i][j] != 0 && empty_board[i][j] == 0) {
                    DrawText(TextFormat("%d", user_board[i][j]), (OFFSET + 15) + j * OFFSET, (OFFSET + 6) + i * OFFSET, 40, BLUE);
                }
            }
        }
        // Cell selecting logic
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mouse_X = GetMouseX();
            int mouse_Y = GetMouseY();
            if (!(mouse_X > OFFSET + CELL_SIZE * 9) && !(mouse_Y > OFFSET + CELL_SIZE * 9) 
                && !(mouse_X < OFFSET) && !(mouse_Y < OFFSET)){
                int clicked_col = (mouse_X - OFFSET) / CELL_SIZE;
                int clicked_row = (mouse_Y - OFFSET) / CELL_SIZE;
                if (clicked_col == selected_cell[1] && clicked_row == selected_cell[0]){
                    selected_cell[1] = -2;
                    selected_cell[0] = -2;
                } else {
                    selected_cell[1] = clicked_col;
                    selected_cell[0] = clicked_row;
                }
            }
        }
        // User's number inserted - numbers from 1 to 9
        if (key_pressed > 48 && key_pressed <= 57) {
            if (selected_cell[0] >= 0 && selected_cell[1] >= 0) {
                user_board[selected_cell[0]][selected_cell[1]] = key_pressed - 48;
            }
        }
        // Delete key - Deletes user's number.
        if (IsKeyPressed(KEY_DELETE)) {
            if (selected_cell[0] >= 0 && selected_cell[1] >= 0) {
                user_board[selected_cell[0]][selected_cell[1]] = 0;
            }
        }
        
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}