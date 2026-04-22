# TermChess-C
A playable, Text-User-interface chess game build on C using ncurses library.
This project allows two users to play chess in terminal.

## Features
- Two-player gameplay (no chessbot)
- Full chess movement rules for all pieces
- Check and checkmate detection
- Stalemate detection
- Pawn promotion
- Highlighting of valid moves
- Move history display
- Save and load game functionality
- Material advantage tracking

## Limitations (Yet to be done)
- Can't play with computer
- Castling and enpassant not implemented
- 
  ## Requirements
- gcc compiler
- ncurses library
- If you don't have ncurses
- run : sudo apt-get install libncurses5-dev libncursesw5-dev (for linux)   
-    brew install ncurses (For Mac)

- ## Compilation
Using Makefile:
make

Or manually:
gcc main.c chessUI.c chessrules.c chessio.c -lncurses -o chess_static
## run 
./chess_static  or if it was linked dynamically then run LD_LIBRARY_PATH=. .chess_dynamic

## Controls

- Arrow Keys → Move cursor
- Enter → Select / Move piece
- S → Save game
- Q → Quit game
- *Valid Move Highlighting [ ]: When you select a piece, all legal destination squares are highlighted with brackets. Because terminal environments have strict color-pairing limitations, this character-overlay method was chosen as the most reliable way to clearly show valid moves without breaking the board's visual contrast.
  ## Save/Load games
Games are saved in the "savedgames/" directory.
Each file stores:
- Board state
- Current player
- Move history
- ##  File Structure
* main.c: Controller - Manages the game loop, user input, and program states.
* chessrules.c / .h: Model - Handles pure mathematical logic, move validation, and check logic.
* chessUI.c / .h: View - Handles all ncurses screen drawing, menus, and color rendering.
* chessio.c / .h: File I/O - Handles writing to and parsing from the savedgames/ directory.
