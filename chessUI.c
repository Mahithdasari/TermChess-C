#include <ncurses.h>
#include <string.h>
#include "chessUI.h"
void draw_square(int Y,int X,int colorpair){
	attron(COLOR_PAIR(colorpair));
	int height =4;
	int width = 8;
	for(int y=0;y<height;y++){
		for(int x=0;x<width;x++){
			mvaddch(Y +y,X+x,' ');
		}
	}
	attroff(COLOR_PAIR(colorpair));
}
void setup_colors(){
	start_color();
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_BLACK,COLOR_GREEN);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	init_pair(4,COLOR_RED,COLOR_GREEN);
	init_pair(5,COLOR_WHITE,COLOR_YELLOW);
	init_pair(6,COLOR_WHITE,COLOR_CYAN);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);   
        init_pair(8, COLOR_BLACK,COLOR_YELLOW);
}
void init_board(char board[8][8]){
	char startingboard[8][8]= {
		{'r','n','b','q','k','b','n','r'},
		{'p','p','p','p','p','p','p','p'},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{'P','P','P','P','P','P','P','P'},
		{'R','N','B','Q','K','B','N','R'},
	};
	for(int r=0;r<8;r++){
	  for(int c =0;c<8;c++){
	  board[r][c] = startingboard[r][c];
	  }
	}
}
void draw_board(char board[8][8],int cursor_r,int cursor_c,int selected_r,int selected_c,int valid_move[8][8]){
	int start_y = (LINES-32)/2;
	int start_x =5;
	//int start_x = (COLS-64)/2;
	attron(A_BOLD);
	for(int c = 0; c < 8; c++){
        char col_label = 'a' + c; 
        mvaddch(start_y + 32, start_x + (c * 8) + 3, col_label);
    }
    for(int r = 0; r < 8; r++){
        char row_label = '8' - r;
        mvaddch(start_y + (r * 4) + 1, start_x - 2, row_label);
    }
    attroff(A_BOLD);
	for(int r=0;r<8;r++){
		for(int c=0;c<8;c++){
			char piece = board[r][c];
			int curr_x = start_x + (c*8);
			int curr_y = start_y + (r*4);
			int colorpair;
			if((r + c) % 2 == 0){// white squares
				if(piece >= 'A' && piece <='Z'){
				colorpair = 3; // red piece in white background
				}
				else colorpair =1;// red in green background
			  }
			else {
			if(piece >= 'A' && piece <='Z'){
			colorpair = 4;
			}
			else{
			colorpair = 2;
			}
			}
			//if(valid_move[r][c] == 1) colorpair =8;
			if(r == cursor_r && c == cursor_c) colorpair =6; //
			if(r== selected_r && c == selected_c) colorpair =5;
			draw_square(curr_y,curr_x,colorpair);
			if(piece != ' '){
			attron(COLOR_PAIR(colorpair) | A_BOLD);
			mvaddch(curr_y+1,curr_x+3,piece);
			attroff(COLOR_PAIR(colorpair)| A_BOLD);
			}
            if (valid_move[r][c] == 1) {
                attron(COLOR_PAIR(colorpair) | A_BOLD);
                mvaddch(curr_y+1, curr_x+2, '[');
                mvaddch(curr_y+1, curr_x+4, ']');
                attroff(COLOR_PAIR(colorpair) | A_BOLD);
            }
			//if(r == cursor_r && c == cursor_c) attroff(A_REVERSE);
		}
	}
	

}
void turn_remainder(int playerno){
  if(playerno == 1){
    mvprintw(10,70,"RED PLAYERS'S TURN (UPPERCASE)");
    }
    else{
    mvprintw(10,70,"BLACK PLAYER'S TURN (LOWERCASE)");
    }
}
void draw_control_panel(int player, char history[256][16], int history_count,int advantage) {
    int start_y = (LINES - 32) / 2;
    int start_x = 72; 
    attron(A_BOLD | COLOR_PAIR(7));
    mvprintw(start_y, start_x,     "=====================================");
    mvprintw(start_y + 1, start_x, "|          TERMINAL CHESS           |");
    mvprintw(start_y + 2, start_x, "=====================================");
    attroff(COLOR_PAIR(7));
    mvprintw(start_y + 4, start_x, "  CURRENT TURN:                      ");
    if (player == 1) {
        attron(COLOR_PAIR(3)); 
        mvprintw(start_y + 6, start_x + 4, "[ RED / UPPERCASE ]            ");
        attroff(COLOR_PAIR(3));
    } else {
        attron(COLOR_PAIR(2)); 
        mvprintw(start_y + 6, start_x + 4, "[ BLACK / LOWERCASE ]          ");
        attroff(COLOR_PAIR(2));
    }
    attron(COLOR_PAIR(7)); 
    mvprintw(start_y + 9, start_x,  "-------------------------------------");
    attroff(COLOR_PAIR(7));
    
    mvprintw(start_y + 10, start_x, "             CONTROLS                ");
    
    attron(COLOR_PAIR(7));
    mvprintw(start_y + 11, start_x, "-------------------------------------");
    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(8));
    mvprintw(start_y + 13, start_x + 2, "ARROWS : Move Cursor               ");
    mvprintw(start_y + 14, start_x + 2, "ENTER  : Select / Move             ");
    mvprintw(start_y + 15, start_x + 2, "S      : Save Game                 ");
    mvprintw(start_y + 16, start_x + 2, "Q      : Quit Match                ");
    attroff(COLOR_PAIR(8));
    // status
    attron(COLOR_PAIR(7));
    mvprintw(start_y + 19, start_x, "-------------------------------------");
    attroff(COLOR_PAIR(7));
    
    mvprintw(start_y + 20, start_x, "           GAME STATUS               ");
    attron(COLOR_PAIR(7));
    mvprintw(start_y + 21, start_x, "-------------------------------------");
        attroff(COLOR_PAIR(7));
    if (advantage > 0) {
        attron(COLOR_PAIR(3)); 
        mvprintw(start_y + 23, start_x + 4, "Material Advantage: RED (+%d)        ", advantage);
        attroff(COLOR_PAIR(3));
    } else if (advantage < 0) {
        attron(COLOR_PAIR(2)); 
        mvprintw(start_y + 23, start_x + 4, "Material Advantage: BLACK (+%d)      ", advantage * (-1));
        attroff(COLOR_PAIR(2));
    } else {
        mvprintw(start_y + 23, start_x + 4, "Both are equal in material        ");
    }

    // Move history
    attron(COLOR_PAIR(7));
    mvprintw(start_y + 25, start_x, "-------------------------------------");
    attroff(COLOR_PAIR(7));
    
    mvprintw(start_y + 26, start_x, "            MOVE HISTORY             ");
    
    attron(COLOR_PAIR(7));
    mvprintw(start_y + 27, start_x, "-------------------------------------");
    attroff(COLOR_PAIR(7));

    int start = 0;
    if (history_count > 5) {
        start = history_count - 5;
    }

    for (int i =0; i < 5; i++) {
        if (start + i < history_count) {
            mvprintw(start_y + 29 + i, start_x + 2, "%d. %s         ", start + i + 1, history[start + i]);
        } else {
            mvprintw(start_y + 29 + i, start_x + 2, "                             ");
        }
    }
    attroff(A_BOLD);
}
void mainmenu(){
  erase();
        mvprintw(10, 45, "============================");
        mvprintw(11, 45, "      TERMINAL CHESS             ");
        mvprintw(12, 45, "============================");
        mvprintw(14, 45, "Press 1: Start New Game         ");
        mvprintw(15, 45, "Press 2: Load Saved Game          ");
        mvprintw(16, 45, "Press 3: Quit");
        refresh();
  }
void load_match(char *load_name) {
    mvprintw(18, 45, "Enter match name (without .txt):               ");
    refresh();
    echo();
   // curs_set(1);
    mvgetnstr(19, 45, load_name, 25);
    noecho();
   // curs_set(0);
}

void save_match(char *custom_name) {
    mvprintw(11, 70, "Enter match name (without .txt):               ");
    refresh();
    echo();
   // curs_set(1);
    mvgetnstr(12, 70, custom_name, 25);
    noecho();
    //curs_set(0);
}

void if_save_success(char *custom_name) {
    attron(COLOR_PAIR(2)); 
    mvprintw(15, 70, "Game saved to %s!                 ", custom_name);
    attroff(COLOR_PAIR(2));
    refresh();
}

void load_error_msg(char *load_name) {
    attron(COLOR_PAIR(3)); 
    mvprintw(21, 45, "Error: Could not find '%s'.              ", load_name);
    attroff(COLOR_PAIR(3));
    mvprintw(22, 45, "Press any key to try again...            ");
    refresh();
}
char if_pawn_promotion(int player) { 
    char new_piece = ' ';
    while(1) { 
        int choice = getch();
        if (player == 1) { 
            if (choice == 'Q' || choice == 'q') { new_piece = 'Q'; break; }
            else if (choice == 'R' || choice == 'r') { new_piece = 'R'; break; }
            else if (choice == 'B' || choice == 'b') { new_piece = 'B'; break; }
            else if (choice == 'N' || choice == 'n') { new_piece = 'N'; break; }
        } 
        else { 
            if (choice == 'Q' || choice == 'q') { new_piece = 'q'; break; }
            else if (choice == 'R' || choice == 'r') { new_piece = 'r'; break; }
            else if (choice == 'B' || choice == 'b') { new_piece = 'b'; break; }
            else if (choice == 'N' || choice == 'n') { new_piece = 'n'; break; }
        }
    }
    return new_piece;
}
