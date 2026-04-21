void draw_square(int Y,int X,int colorpair);
void setup_colors();
void init_board(char board[8][8]);
void draw_board(char board[8][8],int cursor_r,int cursor_c,int selected_r,int selected_c,int valid_moves[8][8]);
void turn_remainder(int playerno);
void draw_control_panel(int player, char history[256][16], int history_count,int advanatge);
void mainmenu();
void mainmenu();
void load_match(char *load_name);
void save_match(char *custom_name);
void if_save_success(char *custom_name);
void load_error_msg(char *load_name);
char if_pawn_promotion(int player);

