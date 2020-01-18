#include <stdio.h>
#include <stdlib.h>
char whichLetter(int grade);

void main(int argc, char const *argv[])
{
	int studentCount, selection, i, grades, index = 1, sum = 0, unsuccessful = 100, successful = 0, successfulIndex, unsuccessfulIndex;
	int a = 0, b = 0, c = 0, d = 0, f = 0; //hangi harf notundan kac tane oldugunu bulmak icin olan degiskenler
	double average;
	char letter;
	srand(40);
	printf("Enter student count:");
	scanf("%d", &studentCount);
	while(studentCount < 3 || studentCount > 50){
		printf("Not in range!!!\n");
		scanf("%d", &studentCount);
		printf("Enter student count:");
	}

	for (i = 0; i < studentCount; ++i)
	{
		grades = 0+rand()%101;
		printf("%d ", grades);
		sum += grades;

		if(grades >= successful){
			successful = grades;
			successfulIndex = index;
		}

		if(grades <= unsuccessful){
			unsuccessful = grades;
			unsuccessfulIndex = index;
		}

		letter = whichLetter(grades);
		switch(letter){
			case 'A':
				a++;
				break;
			case 'B':
				b++;
				break;
			case 'C':
				c++;
				break;
			case 'D':
				d++;
				break;
			case 'F':
				f++;
				break;
		}
		index++;
	}

	average = (double)sum / studentCount;

	do{
		printf("\n\nStudent Score Calculator Menu for %d Student\n", studentCount);
		printf("\n1) Most Successful Student\n");
		printf("2) Most Unsuccessful Student\n");
		printf("3) Letter Grade Statistics\n");
		printf("4) Calculate Average\n");
		printf("5) Show All Data\n");
		printf("Make Selection: ");
		scanf("%d", &selection);
		switch(selection){
			case 1:
				printf("Most Successfully Student:\n");
				printf("Index: %d\n", successfulIndex);
				printf("Score: %d\n", successful);
				printf("Letter Grade: %c\n", whichLetter(successful));
				break;
			case 2:
				printf("Most Unsuccessfully Student:\n");
				printf("Index: %d\n", unsuccessfulIndex);
				printf("Score: %d\n", unsuccessful);
				printf("Letter Grade: %c\n", whichLetter(unsuccessful));
				break;
			case 3:
				printf("%d student got letter grade 'A'\n", a);
				printf("%d student got letter grade 'B'\n", b);
				printf("%d student got letter grade 'C'\n", c);
				printf("%d student got letter grade 'D'\n", d);
				printf("%d student got letter grade 'F'\n", f);
				break;
			case 4:
				printf("The average score of %d students is %.2lf\n", studentCount, average);
				break;
			case 5:
				printf("Most Successfully Student:\n");
				printf("Index: %d\n", successfulIndex);
				printf("Score: %d\n", successful);
				printf("Letter Grade: %c\n\n", whichLetter(successful));
				printf("Most Unsuccessfully Student:\n");
				printf("Index: %d\n", unsuccessfulIndex);
				printf("Score: %d\n", unsuccessful);
				printf("Letter Grade: %c\n\n", whichLetter(unsuccessful));
				printf("%d student got letter grade 'A'\n", a);
				printf("%d student got letter grade 'B'\n", b);
				printf("%d student got letter grade 'C'\n", c);
				printf("%d student got letter grade 'D'\n", d);
				printf("%d student got letter grade 'F'\n\n", f);
				printf("The average score of %d students is %.2lf\n", studentCount, average);
				break;
			case -1:
				return;
			default:
				printf("False selection!!!\n");
		}
	}while(selection != -1);
}

char whichLetter(int grade)
{
	char letter;
	if(grade >= 90 && grade <= 100)
		letter = 'A';
	else if(grade >= 80 && grade <= 89)
		letter = 'B';
	else if(grade >= 70 && grade <= 79)
		letter = 'C';
	else if(grade >= 60 && grade <= 69)
		letter = 'D';
	else if(grade >= 0 && grade <= 59)
		letter = 'F';

	return letter;
}
