# My Sudoku Roadmap

**Idea:** first fix the bugs, then clean up the code, then write the logic, and only at the end make it look nice. One step = one branch.

---

## Step 0: Fix bugs and setup
- [ ] **New puzzle gets broken:** `generate_puzzle` doesn't clear the old board first, so the new "solution" can have duplicates. → Zero the board at the start.
- [ ] **Old numbers stay:** a new puzzle doesn't clear `user_board` or `selected_cell`.
- [ ] **Out of bounds:** clicking exactly on the right/bottom edge (x or y = 500) gives row/col = 9 and writes outside the array. → Use `<` instead of `<=` ([main.c:103](main.c#L103)).
- [ ] **Given cells can be typed into:** block input if the puzzle already has a number there.
- [ ] **Mixed constants:** numbers are drawn with `j * OFFSET` instead of `j * CELL_SIZE` ([main.c:86](main.c#L86)).
- [ ] **Leftovers:** remove the useless `(Vector2){50.0f, 100.0f};` line and the commented-out code.
- [ ] **Magic numbers:** use `KEY_ONE`…`KEY_NINE` instead of `48`/`57`, and also accept Backspace.
- [ ] **Binary in git:** add `sudoku` to `.gitignore` and run `git rm --cached sudoku`.
- [ ] **Makefile:** add `sudoku.c`/`sudoku.h` as dependencies, add `-Wall -Wextra`, and add `clean` and `run` targets.

✅ Done when: it builds with 0 warnings and switching difficulty always gives a valid board.

---

## Step 1: Clean up the code structure
I do this *before* adding features, so the main loop doesn't turn into a mess.

- [ ] **Split into files:**
  - `sudoku.c/h`: solver and generator (no raylib!)
  - `game.c/h`: game state and actions (no raylib!)
  - `ui.c/h`: all drawing and input
  - `main.c`: just the window and the loop
- [ ] **Make a `GameState` struct** instead of loose arrays:
  ```c
  typedef struct {
      int puzzle[9][9];    // the given numbers
      int solution[9][9];
      int board[9][9];     // what the player sees
      int sel_row, sel_col;
      Difficulty difficulty;
  } GameState;
  ```
- [ ] **Break the loop into small functions:** `handle_input()`, `update()`, `draw_game()`, `draw_grid()`, `draw_numbers()`…
- [ ] **Header cleanup:** move `CELL_SIZE`/`OFFSET` to `ui.h`, make internal helpers `static`, use `GRID_SIZE` instead of `9`, fix typos, and set the window title to "Sudoku".

✅ Done when: the game works the same as before, but `main.c` is short and easy to read.

---

## Step 2: Unique puzzles and tests
Hint and mistake checking only make sense when there is exactly **one** solution, so this comes before the features.

- [ ] `init_masks()`: build the row/col/box masks from an existing board.
- [ ] `count_solutions(board, limit)`: like `solve`, but it counts solutions and **stops at 2** (I only need to know "1 or more").
- [ ] **New generator** (replaces `punch_holes`):
  1. Fill a full board with `solve()` → this is the solution
  2. Shuffle the list of all 81 cells
  3. Remove each cell; if `count_solutions != 1`, put it back
  4. Stop when I reach the clue count for the difficulty
- [ ] **Realistic clue counts:** Easy 36–40, Medium 30–35, Hard 26–29, Extreme 22–25. My current Extreme (17–23 clues) is almost impossible to reach.
- [ ] **Tests** in `tests/test_sudoku.c` with `assert`, run with `make test`:
  - solver solves a known puzzle
  - `count_solutions` is 1 on a known unique puzzle and 2 on an empty board
  - 100+ generated puzzles are all unique and valid
- [ ] *(Bonus)* Remove cells in symmetric pairs, like newspaper Sudokus.
- [ ] *(Bonus)* Speed it up: always pick the empty cell with the fewest options.

✅ Done when: `make test` passes and Extreme generates in under 1 second.

---

## Step 3: Game logic (no UI yet)
Each feature is a function in `game.c`. I test it with keyboard shortcuts first; buttons come in Step 4.

- [ ] **New game:** `game_new(gs, difficulty)`
- [ ] **Reset:** `game_reset(gs)` sets the board back to the puzzle, same puzzle.
- [ ] **Place / erase:** `game_place()` / `game_erase()` are the *only* functions that change the board.
- [ ] **Mistakes:** a number is wrong if it doesn't match `solution`. Count the mistakes.
- [ ] **Win check:** when `board == solution`, the status becomes `WON`.
- [ ] **Timer:** add the frame time each frame and stop when I win.
- [ ] **Hint:** fill the selected cell (or a random empty one) from `solution` and count the hints used.
- [ ] **Pencil marks:** `uint16_t notes[9][9]` as a bitmask (bit n = note n). When I place a number, remove it from the notes in the same row, column and box.
- [ ] **Undo / redo** (last, because every action has to save a "move"): a stack of `{row, col, old, new}`.

✅ Done when: everything works with the keyboard, even if it looks plain.

---

## Step 4: Buttons and controls
- [ ] **A `Button` struct** (`Rectangle` + label) with `button_clicked()` and `draw_button()`. No more hand-written hitboxes.
- [ ] **Buttons:** New, Reset, Hint, Undo, Redo, Pencil on/off.
- [ ] **Number pad:** buttons 1–9 and Erase.
- [ ] **Keyboard:** arrows move the selection, 1–9 place, Backspace erases, `N` = pencil, `Ctrl+Z` = undo.

✅ Done when: I can play a full game with only the mouse *or* only the keyboard.

---

## Step 5: Visual feedback
- [ ] Highlight the row, column and box of the selected cell
- [ ] Highlight all cells with the same number
- [ ] Different colors for given, my numbers, hints and mistakes
- [ ] Draw pencil notes as small numbers inside the cell
- [ ] Show the active difficulty and whether pencil mode is on
- [ ] Show timer, mistakes and hints
- [ ] Win screen ("Solved in 04:12!")

---

## Step 6: Make it look nice (last!)
- [ ] One color palette as named constants
- [ ] A nicer font or my digit textures
- [ ] Center the board and use proper spacing (no hard-coded pixels)
- [ ] Resizable window
- [ ] Button hover effects and small animations
- [ ] *(Bonus)* Save and load a game to a file

---

## Step 7: Show it off
- [ ] README with a screenshot or GIF, controls, build steps, and "What I learned"
- [ ] *(Bonus)* GitHub Actions that runs `make test`
- [ ] Tag `v1.0`

---

## Tips for every step
- New branch per step → small commits → merge to `main` → tick the box
- Logic first, then test, then drawing
- Keep 0 warnings. If something acts weird, build with `-fsanitize=address`.
