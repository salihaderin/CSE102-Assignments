#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum block_type{P, S, M, B, T, R};

struct block
{
	char *text;
	int data;
	int type;
	int pos_x;
	int pos_y;
	int jump_x;
	int jump_y;
};

void init_board(struct block board[10][10]);
void print_board(struct block board[10][10]);
int dice_roll(void);
void index_to_member(int index, int *r, int *c);
int member_to_index(int r, int c);
int single_player_game(struct block board[10][10], int currentBlock, int moveCount, int *isFinished, int *forbidded);
int two_player_game(struct block board[10][10]);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int isFinished = 0, forbidded = 0;
	struct block board[10][10];
	init_board(board);
	print_board(board);
	single_player_game(board, 1, 0, &isFinished, &forbidded);
	return 0;
}

void init_board(struct block board[10][10])
{
	int count = 100, i, j;
	for(i = 0; i < 10; ++i){
		if(i % 2 == 0){
			for(j = 9; j >= 0; --j){
				board[i][j].text = NULL;
				board[i][j].type = R;
				board[i][j].data = count;
				board[i][j].pos_x = j;
				board[i][j].pos_y = i;
				count--;
			}
		}
		else if(i % 2 != 0){
			for(j = 0; j < 10; ++j){
				board[i][j].text = NULL;
				board[i][j].type = R;
				board[i][j].data = count;
				board[i][j].pos_x = j;
				board[i][j].pos_y = i;
				count--;
			}
		}
	}
	
	board[0][8].text = "S{56}";
	board[0][8].type = S;
	board[0][8].jump_x = 5;
	board[0][8].jump_y = 4;

	board[0][7].text = "S{72}";
	board[0][7].type = S;
	board[0][7].jump_x = 1;
	board[0][7].jump_y = 2;

	board[0][2].text = "T";
	board[0][2].type = T;
	board[0][2].jump_x = 7;
	board[0][2].jump_y = 1;

	board[1][1].text = "M{94}";
	board[1][1].type = M;
	board[1][1].jump_x = 0;
	board[1][1].jump_y = 3;

	board[1][5].text = "P";
	board[1][5].type = P;

	board[1][8].text = "B";
	board[1][8].type = B;
	board[1][8].jump_x = 3;
	board[1][8].jump_y = 1;

	board[2][2].text = "S{68}";
	board[2][2].type = S;
	board[2][2].jump_x = 2;
	board[2][2].jump_y = 3;

	board[2][5].text = "M{83}";
	board[2][5].type = M;
	board[2][5].jump_x = 7;
	board[2][5].jump_y = 1;

	board[2][8].text = "T";
	board[2][8].type = T;
	board[2][8].jump_x = 3;
	board[2][8].jump_y = 2;

	board[3][1].text = "M{77}";
	board[3][1].type = M;
	board[3][1].jump_x = 6;
	board[3][1].jump_y = 2;

	board[3][4].text = "B";
	board[3][4].type = B;
	board[3][4].jump_x = 0;
	board[3][4].jump_y = 2;

	board[3][7].text = "S{52}";
	board[3][7].type = S;
	board[3][7].jump_x = 1;
	board[3][7].jump_y = 4;

	board[4][3].text = "T";
	board[4][3].type = T;
	board[4][3].jump_x = 1;
	board[4][3].jump_y = 5;

	board[4][6].text = "M{77}";
	board[4][6].type = M;
	board[4][6].jump_x = 6;
	board[4][6].jump_y = 2;

	board[4][9].text = "S{44}";
	board[4][9].type = S;
	board[4][9].jump_x = 6;
	board[4][9].jump_y = 5;

	board[5][0].text = "B";
	board[5][0].type = B;
	board[5][0].jump_x = 4;
	board[5][0].jump_y = 4;

	board[5][2].text = "P";
	board[5][2].type = P;

	board[5][5].text = "S{22}";
	board[5][5].type = S;
	board[5][5].jump_x = 1;
	board[5][5].jump_y = 4;

	board[6][1].text = "M{52}";
	board[6][1].type = M;
	board[6][1].jump_x = 1;
	board[6][1].jump_y = 5;

	board[6][5].text = "B";
	board[6][5].type = B;
	board[6][5].jump_x = 9;
	board[6][5].jump_y = 5;

	board[6][9].text = "T";
	board[6][9].type = T;
	board[6][9].jump_x = 4;
	board[6][9].jump_y = 6;

	board[7][1].text = "B";
	board[7][1].type = B;
	board[7][1].jump_x = 3;
	board[7][1].jump_y = 6;

	board[7][5].text = "S{12}";
	board[7][5].type = S;
	board[7][5].jump_x = 1;
	board[7][5].jump_y = 8;

	board[8][2].text = "P";
	board[8][2].type = P;

	board[8][6].text = "M{28}";
	board[8][6].type = M;
	board[8][6].jump_x = 7;
	board[8][6].jump_y = 2;

	board[9][3].text = "M{11}";
	board[9][3].type = M;
	board[9][3].jump_x = 8;
	board[9][3].jump_y = 0;

	board[9][4].text = "S{1}";
	board[9][4].type = S;
	board[9][4].jump_x = 9;
	board[9][4].jump_y = 9;
}

void print_board(struct block board[10][10])
{
	int i, j; 
	for(i = 0; i < 10; ++i){
		for(j = 0; j < 10; ++j){
			if(board[i][j].text != NULL){
				printf("%s\t", board[i][j].text);
			}
			else
				printf("%d\t", board[i][j].data);
		}
		printf("\n");
	}
}

int dice_roll(void)
{
	return (rand() % 6) + 1;
}

void index_to_member(int index, int *r, int *c)
{
	index--;
	*r = index / 10;
	*r = 9 - *r;
	*c = index % 10;
	if(1 == *r % 2){
		*c = 9- *c;
	}
}

int member_to_index(int r, int c)
{
	int index;
	index = (9 - r) * 10;
	if(0 == r % 2){
		index += c;
	}
	else{
		index += (9 - c);
	}
	return index + 1;
}

int single_player_game(struct block board[10][10], int currentBlock, int moveCount, int *isFinished, int *forbidded)
{
	int r, c, i, tempBlock, status;
	for(i = 6; i >= 1; --i){
		tempBlock = currentBlock + i;
		if(100 == tempBlock){
			*isFinished = 1;
		}
		else if(100 > tempBlock && *forbidded != i){
			moveCount++;
			index_to_member(tempBlock, &r, &c);
			printf("%d: %d + %d = %d\n", moveCount, currentBlock, i, tempBlock);
			switch(board[r][c].type){
			case P:
				*forbidded = i;
				tempBlock -= i;
				break;
			case S:
			case M:
				tempBlock = member_to_index(board[r][c].jump_x, board[r][c].jump_y);
				printf("M: %d\n", tempBlock);
				break;
			case B:
				tempBlock += 5;
				break;
			case T:
				tempBlock -= 5;
				break;
			}
			if(P != board[r][c].type){
				//char c; scanf("%c", &c);
				single_player_game(board, tempBlock, moveCount, isFinished, forbidded);
			}
		}
		if(*isFinished){
			printf("%d\n", i);
			return moveCount;
		}
	}
}