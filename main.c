#include <ncurses.h>
#include <string.h>
#include "chessUI.h"
#include "chessrules.h"
#include "chessio.h"
int main(){
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    setup_colors();
    char board[8][8];
    init_board(board);
    int cursor_r = 0;
    int cursor_c =0;
    int selc_r = -1;
    int selc_c = -1;
    int selected=0;
    int player = 1; // 1 -> UPPERCASE
    int game_started = 0;
    int exit_program = 0;
    char movehistory[256][16]; // stores movehistory
    int move_count=0;
    while(game_started ==0){
        mainmenu();
        int choice = getch();
        if (choice == '1') {
        //New Game
            init_board(board); 
            player = 1;       
            game_started = 1;
            move_count =0;
        }
        else if (choice == '2') { //Loading a game which was already saved
           char match_name[50];
           load_match(match_name);
           strcat(match_name,".txt");
            if (load_game(board, &player,match_name, movehistory, &move_count) == 1) {
                game_started = 1; 
            } else {
               load_error_msg(match_name);
                getch(); 
            }
            }
        else if (choice == '3' || choice == 'q' || choice == 'Q') {
            exit_program = 1;
            break;
        }
    }
    if (exit_program == 1) {
        endwin();
        return 0;
    }
    
    while(1){
      int valid_squares[8][8] ={0}; // square used for highlighting squares which are valid moves from our selected pos
        erase();
        if(selected ==1){
       // selected -> 1 means we have already selcted the piece which is being moved next
        for(int r=0;r<8;r++){
    for(int c=0;c<8;c++){
    if (is_legalmove(board, selc_r, selc_c, r, c)) {
                        char captured = board[r][c];
                        board[r][c] = board[selc_r][selc_c];
                        board[selc_r][selc_c] = ' ';
                        if (is_in_check(board, player) == 0) {
                            valid_squares[r][c] = 1; 
                        }
                        board[selc_r][selc_c] = board[r][c];
                        board[r][c] = captured;
                    }  
        }
      }
      }
        int advantage = material_advantage(board); 
        draw_board(board,cursor_r,cursor_c,selc_r,selc_c,valid_squares);
        draw_control_panel(player, movehistory, move_count,advantage);
        if (has_legal_moves(board,player) == 0){
            if(is_in_check(board,player) == 1){
                if(player == 1) mvprintw(10, 70, "     CHECKMATE! BLACK WINS!            ");
                else mvprintw(10, 70, "    CHECKMATE! RED WINS!               ");
            }
            else{
                mvprintw(10,70,"STALEMATE !! IT'S A DRAW              ");
            }
            mvprintw(12,70,"   Press any key to exit           ");
            refresh();
            getch();
            break;
        }
        else if(is_in_check(board,player) == 1){
            mvprintw(12, 70, "     WARNING: YOUR KING IS IN CHECK!             ");
        }
        refresh();
        int ch = getch();
        if(ch == 'q' || ch =='Q') break;
        else if(ch == KEY_UP && cursor_r > 0) cursor_r--;
        else if(ch == KEY_DOWN && cursor_r < 7) cursor_r++;
        else if(ch == KEY_LEFT && cursor_c > 0) cursor_c--;
        else if(ch == KEY_RIGHT && cursor_c < 7) cursor_c++;
    else if(ch == '\n'){
        char p = board[cursor_r][cursor_c];
    if(selected == 0){
             if( p != ' ' &&((player== 1 && p >= 'A' && p <= 'Z')|| (player ==2 && p >='a' && p<='z'))){
            selc_r = cursor_r;
             selc_c = cursor_c;
            selected = 1;
        }
    }
    else{//selected == 1 i.e already pressed enter once 
        if(is_legalmove(board, selc_r, selc_c, cursor_r, cursor_c)){
            char temp = board[cursor_r][cursor_c];
            board[cursor_r][cursor_c] = board[selc_r][selc_c];
            board[selc_r][selc_c] = ' ';        
            char st_col = 'a' + selc_c;
            char st_row = '8' - selc_r;
            char end_col   = 'a' + cursor_c;
            char end_row   = '8' - cursor_r;
            
            sprintf(movehistory[move_count], "%c: %c%c -> %c%c",board[cursor_r][cursor_c],st_col,st_row, end_col,end_row);
            move_count++;
            if(is_in_check(board,player)) {
                board[selc_r][selc_c] = board[cursor_r][cursor_c];
                board[cursor_r][cursor_c] = temp;
                move_count--;
                mvprintw(10,70,"Invalid move : King is in check                  ");
                mvprintw(11,70,"          Press any key to try again              ");
                refresh();
                getch();
            }
            else{
                if(is_pawnpromotion(board[cursor_r][cursor_c],cursor_r)){
                mvprintw(11,70,"     Pawn PROMOTION             ");
                mvprintw(12,70,"     Press Q ,R ,N or B           ");
                refresh();
               char new_piece = if_pawn_promotion(player);
                    
                    pawn_promotion(board,cursor_r,cursor_c,new_piece);
            }
            if(player == 1) player =2;
            else player =1;
            }
        }
        selected =0;
        selc_r = -1;
        selc_c = -1;
    }
}
else if(ch == 's' || ch == 'S'){
            char matchname[30];
            save_match(matchname);
            strcat(matchname, ".txt");
            save_game(board, player, matchname, movehistory, move_count);
            if_save_success(matchname);
            getch();
        }
        }
    endwin();
    return 0;
}
