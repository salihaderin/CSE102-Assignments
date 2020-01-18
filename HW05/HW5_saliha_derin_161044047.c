#include <stdio.h>

typedef enum{white_man, black_man, white_king, black_king, empty}piece;
typedef enum{white = 10, black = 20}player;
void init_board(piece board[][8]);
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
void sample_game_1();
void sample_game_2();

int main(int argc, char const *argv[])
{
	piece board[8][8];
	init_board(board);
	//sample_game_1();
	sample_game_2();
	return 0;
}

void init_board(piece board[][8])
{
	int i, j;
	for(i = 0; i < 8; ++i){
		for(j = 0; j < 8; ++j){
			if((i == 1) || (i == 2)){
				board[i][j] = black_man;
				printf("b");
			}
			else if((i == 5) || (i == 6)){
				board[i][j] = white_man;
				printf("w");
			}
			else{
				board[i][j] = empty;
				printf("-");
			}
		}
		printf("\n");
	}
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p)
{
	char x;
	int n = 0, i;
	//gidilmeye calisilan yer bos degilse
	if(board[to_y][to_x] != empty){
		return -2;
	}
	for(i = 0; i < 8; ++i){
		if(board[0][i] == white_man)
			board[0][i] = white_king;
		if(board[7][i] == black_man)
			board[7][i] = black_king;
	}
	//BLACK ICIN:
	//kendinin olmayan tasi oynatmaya calisirsa:
	if(p == black && !((board[from_y][from_x] != black_man) ^ (board[from_y][from_x] != black_king))){
		return -1;
	}
	//geri gitmeye calisirsa:
	if(p == black && from_y > to_y && board[from_y][from_x] == black_man){
		return -2;
	}
	else if(p == black && board[from_y][from_x] == black_king && from_y >= to_y){
		for(i = from_y-1; i > to_y; --i){
			//kendi tasinin ustunden atlayamaz diye
			if(board[i][from_x] == black_man || board[i][from_x] == black_king){
				return -2;
			}
			//white mani aldiktan sonraki karede durmasi gerekir
			else if((board[i][from_x] == white_man || board[i][from_x] == white_king) && i != (to_y + 1)){
				return -2;
			}
			else if((board[i][from_x] == white_man || board[i][from_x] == white_king) && i == (to_y + 1)){
				n++;
				board[i][from_x] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = black_king;
				return n;
			}
		}
		board[from_y][from_x] = empty;
		board[to_y][to_x] = black_king;
		return n;
	}
	//ileri gitmeye calisirsa:
	if(p == black && board[from_y][from_x] == black_man && to_y == (from_y+2) && (board[from_y+1][from_x] == white_man || board[from_y+1][from_x] == white_king)){
		n++;
		board[from_y+1][from_x] = empty;
		board[from_y][from_x] = empty;
		board[to_y][to_x] = black_man;
		return n;
	}
	if(p == black && board[from_y][from_x] == black_man && to_y == (from_y+2) && (board[from_y+1][from_x] != white_man || board[from_y+1][from_x] != white_king)){
			return -2;
	}
	if(p == black && board[from_y][from_x] == black_man && to_y == (from_y+1)){
		board[from_y][from_x] = empty;
		board[to_y][to_x] = black_man;
		return n;
	}
	if(p == black && board[from_y][from_x] == black_king && to_y > from_y){
		for(i = from_y; i < to_y; ++i){
			if(board[i][from_x] == black_man || board[i][from_x] == black_king)
				return -2;
			else if((board[i][from_x] == white_man || board[i][from_x] == white_king) && to_y != (i + 1))
				return -2;
			else if((board[i][from_x] == white_man || board[i][from_x] == white_king) && to_y == (i + 1)){
				n++;
				board[i][from_x] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = black_king;
				return n;
			}
		}
		board[from_y][from_x] = empty;
		board[to_y][to_x] = black_king;
		return n;
	}
	//saga gitmeye calisirsa
	//black man icin
	if(p == black && board[from_y][from_x] == black_man && to_x > from_x){
		if(to_x == (from_x+1) && board[to_y][to_x] == empty){
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
			return n;
		}
		if(to_x == (from_x+2) && (board[from_y][from_x+1] == white_man || board[from_y][from_x+1] == white_king)){
			n++;
			board[from_y][from_x+1] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
			return n;
		}
		else 
			return -2;
	}
	//black king icin:
	if(p == black && board[from_y][from_x] == black_king && to_x > from_x){
		for(i = from_x; i < to_x; ++i){
			if((board[from_y][i] == white_man || board[from_y][i] == white_king) && i == (to_x-1)){
				n++;
				board[from_y][i] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = black_king;
				return n;
			}
			if(board[from_y][i] == black_man || board[from_y][i] == black_king)
				return -2;
			if((board[from_y][i] == white_man || board[from_y][i] == white_king) && i != (to_x-1))
				return -2;
		}
		board[from_y][from_x] = empty;
		board[to_y][to_x] = black_king;
		return n;
	}
	//sola gitmeye calisirsa
	//black man icin:
	if(p == black && board[from_y][from_x] == black_man && to_x < from_x){
		if(to_x == (from_x-1) && board[to_y][to_x] == empty){
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
			return n;
		}
		if(to_x == (from_x-2) && (board[from_y][from_x-1] == white_man || board[from_y][from_x-1] == white_king)){
			n++;
			board[from_y][from_x-1] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
			return n;
		}
		else 
			return -2;
	}
	//black king icin:
	if(p == black && board[from_y][from_x] == black_king && to_x < from_x){
		for(i = from_x; i > to_x; --i){
			if((board[from_y][i] == white_man || board[from_y][i] == white_king) && i == (to_x+1)){
				n++;
				board[from_y][i] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = black_king;
				return n;
			}
			if(board[from_y][i] == black_man || board[from_y][i] == black_king)
				return -2;
			if((board[from_y][i] == white_man || board[from_y][i] == white_king) && i != (to_x+1))
				return -2;
		}
		board[from_y][from_x] = empty;
		board[to_y][to_x] = black_king;
		return n;
	}
	//WHITE ICIN:
	//kendinin olmayan tasi oynatmaya calisirsa:
	if(p == white && !((board[from_y][from_x] != white_man) ^ (board[from_y][from_x] != white_king))){
		return -1;
	}
	//geri gitmeye calisirsa:
	if(p == white && to_y > from_y && board[from_y][from_x] == white_man){
		return -2;
	}
	else if(p == white && board[from_y][from_x] == white_king && to_y >= from_y){
		for(i = to_y; i > from_y; --i){
			if(board[i][from_x] == white_man || board[i][from_x] == white_king)
				return -2;
			else if((board[i][from_x] == black_man || board[i][from_x] == black_king) && i != (to_y-1))
				return -2;
			else if((board[i][from_x] == black_man || board[i][from_x] == black_king) && i == (to_y-1)){
				n++;
				board[i][from_x] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = white_king;
			}
		}
		board[from_y][from_x] = empty;
		board[to_y][to_x] = white_king;
		return n;	
	}
	//ileri gitmeye calisirsa:
	if(p == white && board[from_y][from_x] == white_man && to_y == (from_y-2) && (board[from_y-1][from_x] == black_man || board[from_y-1][from_x] == black_king)){
		n++;
		board[from_y-1][from_x] = empty;
		board[from_y][from_x] = empty;
		board[to_y][to_x] = white_man;
		return n;
	}
	if(p == white && board[from_y][from_x] == white_man && to_y == (from_y-2) && (board[from_y-1][from_x] != black_man || board[from_y-1][from_x] != black_king)){
		return -2;
	}
	if(p == white && board[from_y][from_x] == white_man && to_y == (from_y-1)){
		board[from_y][from_x] = empty;
		board[to_y][to_x] = white_man;
		return n;
	}
	if(p == white && board[from_y][from_x] == white_king && to_y < from_y){
		for(i = from_y; i < to_y; --i){
			if(board[i][from_x] == white_man || board[i][from_x] == white_king)
				return -2;
			else if((board[i][from_x] == black_man || board[i][from_x] == black_king) && to_y != (i-1))
				return -2;
			else if((board[i][from_x] == black_man || board[i][from_x] == black_king) && to_y == (i-1)){
				n++;
				board[i][from_x] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = white_king;
				return n;
			}
		}
		board[from_y][from_x] = empty;
		board[to_y][to_x] = white_king;
		return n;
	}
	//saga gitmeye calisirsa
	//white man icin:
		if(p == white && board[from_y][from_x] == white_man && to_x > from_x){
			if(to_x == (from_x+1) && board[to_y][to_x] == empty){
				board[from_y][from_x] = empty;
				board[to_y][to_x] = white_man;
				return n;
			}
			if(to_x == (from_x+2) && (board[from_y][from_x+1] == black_man || board[from_y][from_x+1] == black_king)){
				n++;
				board[from_y][from_x+1] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = white_man;
				return n;
			}
			else 
				return -2;
		}
	// white king icin:
		if(p == white && board[from_y][from_x] == white_king && to_x > from_x){
			for(i = from_x; i < to_x; ++i){
				if((board[from_y][i] == black_man || board[from_y][i] == black_king) && i == (to_x-1)){
					n++;
					board[from_y][i] = empty;
					board[from_y][from_x] = empty;
					board[to_y][to_x] = white_king;
					return n;
				}
				if(board[from_y][i] == white_man || board[from_y][i] == white_king)
					return -2;
				if((board[from_y][i] == black_man || board[from_y][i] == black_king) && i != (to_x-1))
					return -2;
			}
			board[from_y][from_x] = empty;
			board[to_y][to_x] = white_king;
			return n;
		}
	//sola gitmeye calisirsa
	//white man icin:
		if(p == white && board[from_y][from_x] == white_man && to_x < from_x){
			if(to_x == (from_x-1) && board[to_y][to_x] == empty){
				board[from_y][from_x] = empty;
				board[to_y][to_x] = white_man;
				return n;
			}
			if(to_x == (from_x-2) && (board[from_y][from_x-1] == black_man || board[from_y][from_x-1] == black_king)){
				n++;
				board[from_y][from_x-1] = empty;
				board[from_y][from_x] = empty;
				board[to_y][to_x] = white_man;
				return n;
			}
			else 
				return -2;
		}
	//white king icin:
		if(p == white && board[from_y][from_x] == white_king && to_x < from_x){
			for(i = from_x; i > to_x; --i){
				if((board[from_y][i] == black_man || board[from_y][i] == black_king) && i == (to_x+1)){
					n++;
					board[from_y][i] = empty;
					board[from_y][from_x] = empty;
					board[to_y][to_x] = white_king;
					return n;
				}
				if(board[from_y][i] == white_man || board[from_y][i] == white_king)
					return -2;
				if((board[from_y][i] == black_man || board[from_y][i] == black_king) && i != (to_x+1))
					return -2;
			}
			board[from_y][from_x] = empty;
			board[to_y][to_x] = white_king;
			return n;
		}
}

void display_board(piece board[][8])
{
	int i, j;
	for(i = 0; i < 8; ++i){
		for(j = 0; j < 8; ++j){
			if(board[0][j] == white_man){
				printf("W");
				board[0][j] = white_king;
			}
			else if(board[7][j] == black_man){
				printf("B");
				board[7][j] = black_king;
			}
			else if(board[i][j] == white_man)
				printf("w");
			else if(board[i][j] == black_man)
				printf("b");
			else if(board[i][j] == white_king)
				printf("W");
			else if(board[i][j] == black_king)
				printf("B");
			else
				printf("-");
		}
		printf("\n");
	}
}

int check_end_of_game(piece board[][8])
{
	int b = 0, w = 0, i, j;
	for(i = 0; i < 8; ++i){
		for(j = 0; j <8; ++j){
			if(board[i][j] == black_man || board[i][j] == black_king)
				b++;
			if(board[i][j] == white_man || board[i][j] == white_king)
				w++;
		}
	}
	if(b == 0)
		return white;
	else if(w == 0)
		return black;
	else
		return -1;
}

void sample_game_2()
{
	printf("SAMPLE GAME 2\n");
	piece board2[8][8];
	int i;
	for(i = 0; i < 8; ++i){
		board2[0][i] = empty;
		board2[7][i] = empty;
	}
	board2[1][0] = empty;
	board2[1][1] = empty;
	board2[1][2] = black_man;
	board2[1][3] = black_man;
	board2[1][4] = black_man;
	board2[1][5] = black_man;
	board2[1][6] = empty;
	board2[1][7] = empty;

	board2[2][0] = empty;
	board2[2][1] = black_man;
	board2[2][2] = black_man;
	board2[2][3] = black_man;
	board2[2][4] = black_man;
	board2[2][5] = empty;
	board2[2][6] = black_man;
	board2[2][7] = black_man;

	board2[3][0] = black_man;
	board2[3][1] = black_man;
	board2[3][2] = black_man;
	board2[3][3] = empty;
	board2[3][4] = empty;
	board2[3][5] = black_man;
	board2[3][6] = empty;
	board2[3][7] = black_man;

	board2[4][0] = empty;
	board2[4][1] = empty;
	board2[4][2] = white_man;
	board2[4][3] = white_man;
	board2[4][4] = white_man;
	board2[4][5] = black_man;
	board2[4][6] = white_man;
	board2[4][7] = white_man;

	board2[5][0] = white_man;
	board2[5][1] = white_man;
	board2[5][2] = white_man;
	board2[5][3] = white_man;
	board2[5][4] = white_man;
	board2[5][5] = empty;
	board2[5][6] = white_man;
	board2[5][7] = white_man;

	board2[6][0] = empty;
	board2[6][1] = empty;
	board2[6][2] = white_man;
	board2[6][3] = white_man;
	board2[6][4] = white_man;
	board2[6][5] = white_man;
	board2[6][6] = empty;
	board2[6][7] = empty;

	display_board(board2);
	printf("\n\n");
	move(board2, 1, 5, 1, 4, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 1, 3, 1, 5, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 4, 3, 3, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 5, 4, 3, 4, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 4, 1, 4, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 3, 1, 3, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 1, 3, 1, 1, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 2, 1, 0, 1, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 5, 3, 4, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 1, 5, 3, 5, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 5, 5, 5, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 5, 5, 5, 7, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 4, 3, 3, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 3, 2, 3, 4, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 6, 5, 5, 5, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 5, 7, 5, 4, black);
	display_board(board2);
	printf("\n\n");
	move(board2, 6, 4, 4, 4, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 4, 4, 2, 4, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 2, 4, 0, 4, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 0, 4, 0, 2, white);
	display_board(board2);
	printf("\n\n");
	move(board2, 0, 2, 0, 0, white);
	display_board(board2);
	printf("\n\n");
}

void sample_game_1()
{
	piece board1[8][8];
	init_board(board1);
	printf("SAMPLE GAME 1\n");
	move(board1, 0, 2, 0, 2, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 5, 4, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 7, 2, 7, 3, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 7, 5, 7, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 7, 3, 7, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 7, 5, 7, 7, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 4, 4, 3, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 2, 4, 4, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 5, 2, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 7, 7, 6, 7, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 5, 6, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 7, 6, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 5, 4, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 5, 2, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 5, 2, 3, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 1, 5, 2, 5, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 3, 7, 3, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 4, 5, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 4, 6, 4, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 3, 6, 3, 5, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 4, 6, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 3, 5, 3, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 1, 2, 0, 2, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 5, 4, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 7, 6, 4, 6, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 4, 6, 4, 4, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 6, 3, 6, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 5, 6, 6, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 5, 2, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 6, 6, 6, 7, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 0, 5, 0, 4, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 0, 3, 0, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 0, 5, 0, 7, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 4, 2, 3, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 2, 2, 4, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 2, 4, 4, 4, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 1, 6, 1, 5, white);
	display_board(board1);
	printf("\n\n");
	move(board1, 0, 7, 0, 5, black);
	display_board(board1);
	printf("\n\n");
	move(board1, 3, 6, 3, 5, white);
	display_board(board1);
	printf("\n\n");

}