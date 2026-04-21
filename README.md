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

- ## Compilation
Using Makefile:
make

Or manually:
gcc main.c chessUI.c chessrules.c chessio.c -lncurses -o chess_static

## Controls

- Arrow Keys → Move cursor
- Enter → Select / Move piece
- S → Save game
- Q → Quit game
- 
  ## Save/Load games
Games are saved in the "savedgames/" directory.
Each file stores:
- Board state
- Current player
- Move history
