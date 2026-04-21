#include <stdio.h>
#include <string.h>
#include "chessio.h"
void save_game(char board[8][8], int player, char *filename,char movehistory[256][16],int move_count) {
        char filepath[100] = "savedgames/";
        strcat(filepath,filename);
        FILE *fptr = fopen(filepath, "w");
    if (fptr == NULL) return; 
    fprintf(fptr, "%d\n", player);
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
           if (board[r][c] == ' ') {
                fprintf(fptr, "- "); 
            } 
            else
             {fprintf(fptr, "%c ", board[r][c]); 
            }
        }}
        fprintf(fptr, "\n"); 
        fprintf(fptr, "%d\n", move_count);
        for (int i = 0; i < move_count; i++) {
        fprintf(fptr, "%s\n", movehistory[i]);
    }
    fclose(fptr); 
}

int load_game(char board[8][8], int *player, char *filename,char movehistory[256][16],int *move_count) {
        char filepath[100]= "savedgames/";
        strcat(filepath,filename);
    FILE *fptr = fopen(filepath, "r");
    if (fptr == NULL) {
        return 0;
    }
    fscanf(fptr, "%d", player);
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            fscanf(fptr, " %c", &board[r][c]);
            if(board[r][c] == '-'){
                board[r][c] = ' ';
            } 
        }
    }
    if (fscanf(fptr, "%d", move_count) == 1) {
        for (int i = 0; i < *(move_count); i++) {
            fscanf(fptr, " %[^\n]", movehistory[i]); 
        }
    }
        else{
            *move_count =0;
        }
    
    fclose(fptr);
    return 1; 
}