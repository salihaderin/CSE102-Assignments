#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Forest{
	char **map;
	int width;
	int heigth;
	int flower_x;
	int flower_y;
};

struct Botanist{
	int coord_x;
	int coord_y;
	int water_bottle_size;
};

void init_game(struct Forest * forest, struct Botanist * botanist);
void print_map(struct Forest forest);
void search(struct Forest * forest, struct Botanist * botanist);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int i;
	struct Forest * forest;
	struct Botanist * botanist;
	forest = (struct Forest *)malloc(sizeof(struct Forest));
	botanist = (struct Botanist *)malloc(sizeof(struct Botanist));
	init_game(forest, botanist);
	print_map(*forest);
	printf("Searching...\n");
	search(forest, botanist);
	for(i = 0; i < forest->width; ++i){
		free(forest->map[i]);
	}
	free(forest->map);
	free(forest);
	free(botanist);
	return 0;
}

void init_game(struct Forest * forest, struct Botanist * botanist)
{
	int i = 0, j = 0;
	char ch;
	FILE * fp;
	fp = fopen("init.csv", "r");
	fscanf(fp, "%d", &botanist->water_bottle_size);
	fscanf(fp, "%d", &forest->heigth);
	ch = fgetc(fp);
	fscanf(fp, "%d", &forest->width);
	ch = fgetc(fp);
	ch = fgetc(fp);
	forest->map = (char **)calloc(forest->heigth, sizeof(char *));
	for(i = 0; i < forest->heigth; ++i){
		forest->map[i] = (char *)calloc(forest->width, sizeof(char));
	}
	i = 0;
	while(!feof(fp)){
		fscanf(fp, "%c", &ch);
		if(ch == '\n'){
			i++;
			j = 0;
		}
		else if(ch != ','){
			if(ch == 'B'){
			}
			forest->map[i][j] = ch;
			j++;
		}
	}
	for(i = 0; i < forest->heigth; ++i){
		for(j = 0; j < forest->width; ++j){
			if(forest->map[i][j] == 'B'){
				botanist->coord_y = i;
				botanist->coord_x = j;
			}
		}
	}
	fclose(fp);
}

void print_map(struct Forest forest)
{
	int i, j;
	for(i = 0; i < forest.heigth; ++i){
		for(j = 0; j < forest.width; ++j){
			printf("%c", forest.map[i][j]);
		}
		printf("\n");
	}
}

void search(struct Forest * forest, struct Botanist * botanist)
{
	//printf("I am on (%d, %d)\n", botanist->coord_y, botanist->coord_x);
	if(forest->map[botanist->coord_y][botanist->coord_x] == 'F'){
		printf("skldjflskdj\n");
		printf("I have found it on (%d, %d)!\n", botanist->coord_y, botanist->coord_x);
		print_map(*forest);
		return;
	}
	if(forest->map[botanist->coord_y][botanist->coord_x] != 'F' && botanist->water_bottle_size == 0){
		print_map(*forest);
		printf("Help! I am on(%d, %d)\n", botanist->coord_y, botanist->coord_x);
		return;
	}
	int r = rand() % 4 + 1;
	switch(r){
		case 1:
			if(forest->map[botanist->coord_y][botanist->coord_x + 1] != ' ' || botanist->coord_x + 1 > forest->width - 1)
				search(forest, botanist);
			else if(forest->map[botanist->coord_y][botanist->coord_x + 1] == 'F'){
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_x++;
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			else{
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_x++;
				forest->map[botanist->coord_y][botanist->coord_x] = 'B';
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			break;
		case 2:
			if(forest->map[botanist->coord_y][botanist->coord_x - 1] != ' ' || botanist->coord_x - 1 < 0)
				search(forest, botanist);
			else if(forest->map[botanist->coord_y][botanist->coord_x - 1] == 'F'){
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_x--;
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			else{
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_x--;
				forest->map[botanist->coord_y][botanist->coord_x] = 'B';
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			break;
		case 3:
			if(forest->map[botanist->coord_y - 1][botanist->coord_x] != ' ' || botanist->coord_y - 1 < 0)
				search(forest, botanist);
			else if(forest->map[botanist->coord_y - 1][botanist->coord_x] == 'F'){
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_y--;
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			else{
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_y--;
				forest->map[botanist->coord_y][botanist->coord_x] = 'B';
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			break;
		case 4:
			if(botanist->coord_y + 1 > forest->width - 1 || forest->map[botanist->coord_y + 1][botanist->coord_x] != ' ')
				search(forest, botanist);
			else if(forest->map[botanist->coord_y + 1][botanist->coord_x] == 'F'){
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_y++;
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			else{
				forest->map[botanist->coord_y][botanist->coord_x] = ' ';
				botanist->coord_y++;
				forest->map[botanist->coord_y][botanist->coord_x] = 'B';
				botanist->water_bottle_size--;
				search(forest, botanist);
			}
			break;
		default:
			printf("Error\n");
			break;
	}
}
