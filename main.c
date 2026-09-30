#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <string.h>

int main() {
    // Constant numbers in asci code.
    const int KEY_ONE = 49, KEY_TWO = 50, KEY_THREE = 51, 
            KEY_FOUR = 52, KEY_FIVE = 53,KEY_SIX = 54,
            KEY_SEVEN = 55, KEY_EIGHT = 56, KEY_NINE = 57;
    srand((unsigned int)time(NULL));

    // Generating the Sudoku
    int empty_board[9][9] = {0};
    int answer_board[9][9] = {0}; // For comparing the user's choice
    int user_board[9][9] = {0}; // User's typed numbers
    generate_puzzle(empty_board, answer_board, EXTREME);

    // # ============ Main Game Logic ============ #
    InitWindow(1000, 600, "Hello raylib");

    int selected_cell[2] ={-2,-2};
    // int check = GetKeyPressed();
    // printf(" The delete ascii: %d", check);
    // # ============ Game Loop ============ #
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
        
        DrawRectangle(OFFSET + CELL_SIZE * selected_cell[1], OFFSET + CELL_SIZE * selected_cell[0],CELL_SIZE - 1, CELL_SIZE - 1, Fade(BLUE, 0.3f));
        // Drawing the Difficulty choice and buttons
        DrawText("Difficulty:" , OFFSET + 9 * CELL_SIZE + 20, OFFSET, 20, Fade(GRAY, 0.8f));
        // Easy Button Draw
        DrawRectangle(630, OFFSET, 50, 23, Fade(ORANGE, 0.5f));
        DrawText("Easy", 630, OFFSET, 20 ,BLACK);
        // Medium Button Draw
        DrawRectangle(690, OFFSET, 70, 23, Fade(ORANGE, 0.5f));
        DrawText("Medium", 690, OFFSET, 20 ,BLACK);
        // Hard Button Draw
        DrawRectangle(770, OFFSET, 50, 23, Fade(ORANGE, 0.5f));
        DrawText("Hard", 770, OFFSET, 20 ,BLACK);
        // Extreme Button Draw
        DrawRectangle(830, OFFSET, 85, 23, Fade(ORANGE, 0.5f));
        DrawText("Extreme", 830, OFFSET, 20 ,BLACK);

        // #====== Difficulty Button Logic
        // EASY Button Press
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() >= 630) && (GetMouseX() <= 680) && (GetMouseY() >= OFFSET) && (GetMouseY() <= 73)){
            generate_puzzle(empty_board,answer_board, EASY);
        }
        // MEDIUM Button Press
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() >= 690) && (GetMouseX() <= 760) && (GetMouseY() >= OFFSET) && (GetMouseY() <= 73)){
            generate_puzzle(empty_board,answer_board, MEDIUM);
        }
        // Hard Button Press
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() >= 770) && (GetMouseX() <= 820) && (GetMouseY() >= OFFSET) && (GetMouseY() <= 73)){
            generate_puzzle(empty_board,answer_board, HARD);
        }
        // Extreme Button Press
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() >= 830) && (GetMouseX() <= 915) && (GetMouseY() >= OFFSET) && (GetMouseY() <= 73)){
            generate_puzzle(empty_board,answer_board, EXTREME);
        }

        // Draw the permenant numbers
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                // Draw the permanent sudoku numbers
                if(empty_board[i][j] != 0) {
                    DrawText(TextFormat("%d", empty_board[i][j]), (OFFSET + 15) + j * CELL_SIZE, (OFFSET + 6) + i * OFFSET, 40, BLACK);
                }
                // Draw user's numbers
                if (user_board[i][j] != 0 && empty_board[i][j] == 0 && empty_board[i][j] == 0) {
                    if (check_user_choice(empty_board, user_board, i, j)) {
                        DrawText(TextFormat("%d", user_board[i][j]), (OFFSET + 15) + j * CELL_SIZE, (OFFSET + 6) + i * OFFSET, 40, BLUE); // Draw user's numbers in blue
                    } else {
                        DrawText(TextFormat("%d", user_board[i][j]), (OFFSET + 15) + j * CELL_SIZE, (OFFSET + 6) + i * OFFSET, 40, RED); // Draw invalid user's numbers in red
                    }
                }
            }
        }
        // Cell selecting logic
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mouse_X = GetMouseX();
            int mouse_Y = GetMouseY();
            if (mouse_X >= OFFSET && mouse_X < OFFSET + + CELL_SIZE * 9 &&
                mouse_Y >= OFFSET && mouse_Y < OFFSET + CELL_SIZE * 9) {
                int clicked_col = (mouse_X - OFFSET) / CELL_SIZE;
                int clicked_row = (mouse_Y - OFFSET) / CELL_SIZE;
                if (empty_board[clicked_row][clicked_col] == 0) { // Disabled user to select board's numbers
                    if (clicked_col == selected_cell[1] && clicked_row == selected_cell[0]){
                        selected_cell[1] = -2;
                        selected_cell[0] = -2;
                    } else {
                        selected_cell[1] = clicked_col;
                        selected_cell[0] = clicked_row;
                    }
                }
            }
        }
        // User's number inserted - numbers from 1 to 9
        if (key_pressed >= KEY_ONE && key_pressed <= KEY_NINE) {
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
    print_board(user_board);
    print_board(empty_board);
    return 0;
}