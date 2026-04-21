#include "chessrules.h"
int is_samecolor(char p1,char p2){
	if(p1 == ' ' || p2 == ' ') return 0;

	if ((p1 >='a' && p1 <='z') && (p2 >='a' && p2 <='z')) return 1;
	else if ((p1 >='A' && p1 <='Z') && (p2 >='A' && p2 <='Z')) return 1;
	else return 0;
}

int is_valid_knightmove(int start_r,int start_c,int end_r,int end_c){
	int y= start_r- end_r;
	int x = start_c- end_c;
	if(x<0) x*= -1;
	if(y <0) y*= -1;
	if((x ==1 && y==2) || (x ==2 && y==1)){
		return 1;
	}
	else{
		return 0;}
}
int is_valid_rookmove(char board[8][8],int sr,int sc,int er,int ec){
    if((sr != er) && (sc != ec)) return 0;
    
    if(sr == er){
    int move = 1;
        if(ec - sc <0){
        move = -1;
        }
        int c= sc + move;
        while(c != ec){
        if(board[sr][c] != ' ') return 0;
        c = c + move;
        }
    }
     else if(sc == ec){
    int move = 1;
        if(er - sr <0){
        move = -1;
        }
        int r = sr + move;
        while(r != er){
        if(board[r][sc] != ' ') return 0;
        r = r + move;
        }
    }
    return 1;
}
int is_valid_bishopmove(char board[8][8],int sr,int sc,int er,int ec){
int r = er - sr;
int r_mv =1;
int c_mv =1;
int c = ec - sc;
if(r < 0) {
  r = r*(-1);
  r_mv = -1;
}
if(c < 0) {
    c = c *(-1);
    c_mv = -1;
    }
    if(r != c){
    return 0;
    }
    sr = sr + r_mv;
    sc = sc + c_mv;
while ((sr != er )){
if(board[sr][sc] != ' ') return 0;
sr = sr + r_mv;
sc = sc + c_mv;
}
    return 1;
}
int is_valid_queenmove(char board[8][8],int sr,int sc,int er,int ec){
if(sr == er || sc ==ec) return is_valid_rookmove(board,sr,sc,er,ec);
else return  is_valid_bishopmove(board,sr,sc,er,ec);

}
int is_valid_kingmove(char board[8][8],int sr,int sc,int er,int ec){
if(sr == er && sc == ec) return 0;
int diff_r = er - sr;
int diff_c = ec -sc;
if(diff_r < 0) {
diff_r = -diff_r;
}
if(diff_c < 0) {
    diff_c = -diff_c;
  }

if(diff_r <=1 && diff_c <= 1) return 1;
else return 0;
}
int is_valid_pawnmove(char board[8][8],int sr,int sc,int er,int ec){
char p =board[sr][sc];
int direction;
int begining_row;
if( p >='A' && p <= 'Z') {
// piece belong to white i.e intially pieces are present at bottom rows and pawns has to move up so row number will decrease
direction = -1;
begining_row = 6; //zero indexed 
}
else {
direction = 1;
begining_row = 1;
}
 if (sc == ec){
        if (er == sr + direction){
            if (board[er][ec] == ' '){
                return 1;
            }
        }
        // two steps
        if (sr == begining_row){
            if (er == sr + 2 * direction){
                if (board[sr + direction][sc] == ' ' && board[er][ec] == ' '){
                    return 1;
                }
            }
        }
    }

    // diagonal capture
    if ((er == sr + direction) &&(ec == sc + 1 || ec == sc - 1)){
            if (board[er][ec] != ' '){
                return 1;
            }
    }

    return 0;
}
int is_legalmove(char board[8][8],int start_r,int start_c,int end_r,int end_c){
        if(start_r == end_r && start_c == end_c) return 0;
	if (end_r < 0 || end_r > 7 || end_c < 0 || end_c > 7) {
		return 0; 
	}
	if (start_r < 0 || start_r > 7 || start_c < 0 || start_c > 7) {
		return 0; 
	}
	char initial = board[start_r][start_c];
	if(initial == ' ') return 0;
	char final = board[end_r][end_c];
	if(is_samecolor(initial,final)) {
	        return 0;
	}
	if(initial == 'R' || initial == 'r') return is_valid_rookmove(board,start_r,start_c,end_r,end_c);
	else if(initial == 'B' || initial == 'b') return is_valid_bishopmove(board,start_r,start_c,end_r,end_c);
	else if(initial == 'Q' || initial == 'q') return is_valid_queenmove(board,start_r,start_c,end_r,end_c);
	else if(initial == 'K' || initial == 'k') return is_valid_kingmove(board,start_r,start_c,end_r,end_c);
	else if(initial == 'P' || initial == 'p') return is_valid_pawnmove(board,start_r,start_c,end_r,end_c);
	else if(initial == 'N' || initial == 'n') return is_valid_knightmove(start_r,start_c,end_r,end_c);
	else return 0;
}
int is_square_underattack(char board[8][8],int R,int C,int enemyplayer){
    for(int r=0;r<=7;r++){
        for(int c=0;c<8;c++){
            char piece = board[r][c];
            if(piece == ' ') continue;
            int is_enemy =0;
            if(enemyplayer == 1 &&(piece >='A' && piece <='Z')) is_enemy=1;
            else if(enemyplayer == 2 &&(piece >='a' && piece <='z')) is_enemy=1;
            if(is_enemy){
                if(piece == 'R' || piece == 'r'){
                    if(is_valid_rookmove(board,r,c,R,C)) return 1;
                }
                else if(piece == 'B'|| piece == 'b'){
                    if(is_valid_bishopmove(board,r,c,R,C)) return 1;
                }
                else if(piece == 'Q'|| piece == 'q'){
                    if(is_valid_queenmove(board,r,c,R,C)) return 1;
                }
                else if(piece == 'N'|| piece == 'n'){
                    if(is_valid_knightmove(r,c,R,C)) return 1;
                }
                else if(piece == 'K' || piece == 'k'){
                    if(is_valid_kingmove(board,r,c,R,C)) return 1;
                }
                else if(piece == 'P' || piece == 'p'){
                    int dir =0;
                    if(enemyplayer == 1) dir = -1; 
                    else dir =1;
                    if(R == r+dir &&(C ==c+1 || C == c-1)) return 1;
                }
                
            }
        }
    }
    return 0;
}
int is_in_check(char board[8][8],int player){
    char king;
    if(player == 1) king = 'K';
    else if(player == 2) king ='k';
    int king_r =9;
    int king_c = 9;
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            if(board[r][c] == king){
                king_r = r;
                king_c = c;
                break;
            }
        }
        if(king_r != 9) break;
    }
    int enemy =0;
    if(player == 1) enemy =2;
    else enemy =1;
    return is_square_underattack(board,king_r,king_c,enemy);
}
int has_legal_moves(char board[8][8],int player){
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            char piece = board[r][c];
            if(piece ==' ') continue;
            int is_sameteam =0;
            if(player ==1 &&(piece >='A' && piece <='Z')) is_sameteam =1;
            else if(player ==2 &&(piece >='a' && piece <='z')) is_sameteam =1;
            if(is_sameteam){
                for(int R=0;R<8;R++){
                    for(int C=0;C<8;C++){
                        if(is_legalmove(board,r,c,R,C)){
                            char captured = board[R][C];
                            board[R][C] = piece;
                            board[r][c] = ' ';
                            int is_kingindanger = is_in_check(board,player);
                            board[R][C] = captured;
                            board[r][c] = piece;
                            if(is_kingindanger == 0) return 1;
                        }
                    }
                }
            }
            
        }
    }
    return 0;
}
int is_pawnpromotion(char piece,int end_r){
    if(piece == 'P' && end_r ==0) return 1;
    else if(piece =='p' && end_r == 7) return 1;
    return 0;
}
void pawn_promotion(char board[8][8],int r,int c,char newpiece){
    board[r][c] = newpiece;
}
int material_advantage(char board[8][8]) {
    int white_score = 0;
    int black_score = 0;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
        char piece = board[r][c];
            switch (piece) {
                case 'P': white_score += 1; break;
                case 'N': white_score += 3; break;
                case 'B': white_score += 3; break;
                case 'R': white_score += 5; break;
                case 'Q': white_score += 9; break;
                case 'p': black_score += 1; break;
                case 'n': black_score += 3; break;
                case 'b': black_score += 3; break;
                case 'r': black_score += 5; break;
                case 'q': black_score += 9; break;
                default: break; 
            }
        }
    }
    return white_score - black_score;
    //calculates the current difference +ve = Advantage for red 
}
