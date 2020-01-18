#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void menu();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);
void horseRacingGame();
void countOccurrence();
void triangleOfSequences();
int main(int argc, char const *argv[])
{
	srand(time(0));
	menu();
	return 0;
}

void menu()
{
	int choice;
	do{
		printf("1. Horse Racing Game\n");
		printf("2. Occurence Counter\n");
		printf("3. Triangle of Sequences\n");
		printf("0. Exit\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				horseRacingGame();
				break;
			case 2:
				countOccurrence();
				break;
			case 3:
				triangleOfSequences();
				break;
			case 0:
				return;
				break;
			default:
				printf("invalid choice\n");
				scanf("%d", &choice);
				break;
		}
	}while(choice != 0);
}

void countOccurrence()
{
	int bigNumber, searchNumber, x, order = 1, occurence = 0;
	printf("Enter two positive integer: ");
	scanf("%d", &bigNumber);
	scanf("%d", &searchNumber);
	while(bigNumber < searchNumber){
		printf("First number should be greater than second number!\n");
		printf("Enter two positive integer: ");
		scanf("%d", &bigNumber);
		scanf("%d", &searchNumber);
	}
	x = searchNumber;
	while(x >= 10){
		x /= 10;
		order++;
	}
	if(bigNumber == searchNumber)
		occurence++;
	else{
		x = pow(10, order);
		while(bigNumber >= searchNumber){
			if(bigNumber % x == searchNumber)
			{
				occurence++;
			}
			bigNumber /= 10;
		}
	}
	printf("%d\n", occurence);
}

void triangleOfSequences()
{
	int line, i, j;
	line = numberGeneratorBetweenRange(2, 10);
	for (i = 1; i <= line; ++i)
	{
		for (j = 1; j <= i; ++j)
		{
			printf("%d ", i * j);
		}
		printf("\n");
	}
}

int getInt(int mini, int maxi)
{
	int num;
	do{
		printf("Horse Number: ");
		scanf("%d", &num);
	}while(num < mini || num > maxi);
	return num;
}

int numberGeneratorBetweenRange(int min, int max)
{
	int num = rand() % ((max + 1) - min) + min;
	return num;
}

void horseRacingGame()
{
	int time, winner = 0, winnerTime = 21, i, j;
	int num = numberGeneratorBetweenRange(3, 5);
	printf("Number of Horse: %d\n", num);
	int horseNumber = getInt(1, num);
	printf("Racing starts...\n");
	for (i = 1; i <= num ; ++i)
	{
		printf("Horse Number: %d", i);
		time = numberGeneratorBetweenRange(10, 20);
		if(time <= winnerTime){
			if(winner != horseNumber){
				winnerTime = time;
				winner = i;
			}
		}
		for (j = 0; j < time; ++j)
		{
			printf("-");
		}
		printf("\n");
	}
	if(horseNumber == winner){
		printf("You win! Winner is Horse %d\n", winner);
	}
	else
		printf("You lose! Winner is Horse %d\n", winner);
}
