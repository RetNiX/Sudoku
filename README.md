# Sudoku — a C learning project

A playable desktop Sudoku game written in C using [raylib] for GUI.

Building this while teaching myself the fundamentals of the C programming language. The goal is to get hands-on practice with C and also learn to use Git and Git-Hub.

## What I learned building this

- Comming soon... :)

## Features

- Difficulty selection: Easy, Medium, Hard, Extreme.
- Controls: both with keyboard and mouse.
- Generate different puzzles everytime.
- More to come..

---

## Progress checklist

Things I want to add to round the project out and make it look polished.

### Gameplay
- [ ] On-screen number pad (click `1`–`9` instead of only typing).
- [ ] Hint button + logic (reveal one correct cell from the stored solution).
- [ ] Pencil marks / candidate notes in a cell.
- [ ] Highlight the row, column, and box of the selected cell.
- [ ] Highlight every other cell that holds the same number as the selected one.
- [ ] Win detection when the board is filled correctly, with a win screen.
- [ ] "New game" and "Restart puzzle" buttons.
- [ ] Undo / redo steps.

### Polish
- [ ] Draw digits with the `textures` instead of `Raylib Fonts`.
- [ ] Timer, plus a mistake counter.
- [ ] Show which difficulty button is currently active.
- [ ] Consistent color palette and spacing; move magic numbers into named constants.
- [ ] Resizable window / scale the board to the window size.

### Code quality ("Good habit list")
- [ ] Split the giant game loop in `main.c` into small functions
  (`draw_grid`, `draw_numbers`, `handle_input`, ...).
- [ ] Move board state into a `struct GameState` instead of loose arrays.
- [ ] Add a proper `Makefile` and learn about it.
- [ ] Unit tests for all the big functions.
- [ ] Guarantee generated puzzles have a unique solution.
- [ ] Add a short GIF or screenshot to this README.
- [ ] Document the build in one command on a any machine.
