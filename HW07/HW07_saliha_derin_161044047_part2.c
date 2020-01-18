#include <stdio.h>
#include <string.h>
int parse_date(char * date, int * day, int * month, int * year);
int is_date_right(int * from_day, int * from_month, int * from_year, int * to_day, int * to_month, int * to_year);
void generate_dates(int * from_day, int * from_month, int * from_year, int * to_day, int * to_month, int * to_year);
int is_leap_year(int * year);
int main(int argc, char const *argv[])
{
	int x, y;
	int * to_day, * to_month, * to_year, * from_day, * from_month, * from_year;
	FILE * fp = fopen("input_date.txt", "w");
	char * start_date, * end_date;
	do{
		printf("Enter start date\n");
		scanf("%s", start_date);
		printf("Enter end date\n");
		scanf("%s", end_date);
		x = parse_date(start_date, &from_day, &from_month, &from_year);
		y = parse_date(end_date, &to_day, &to_month, &to_year);
	}while(x != 1 || y != 1);
	fclose(fp);
	return 0;
}

int parse_date(char * date, int * day, int * month, int * year)
{
	if(date[0] > 47 && date[0] < 58){
		*day = (date[0] - '0') * 10;
	}
	else
		return 0;
	if(date[1] > 47 && date[1] < 58){
		*day += (date[1] - '0');
	}
	else
		return 0;
	if(date[2] != '/')
		return 0;
	if(date[3] > 47 && date[3] < 58){
		*month = (date[3] - '0') * 10;
	}
	else
		return 0;
	if(date[4] > 47 && date[4] < 58){ 
		*month += (date[4] - '0');
	}
	else
		return 0;
	if(date[5] != '/')
		return 0;
	if(date[6] > 48 && date[6] < 58){
		*year = (date[6] - '0') * 1000;
	}
	else
		return 0;
	if(date[7] > 47 && date[7] < 58){
		*year += (date[7] - '0') * 100;
	}
	else 
		return 0;
	if(date[8] > 47 && date[8] < 58){
		*year += (date[8] - '0') * 10;
	}
	else 
		return 0;
	if(date[9] > 47 && date[9] < 58){
		*year += (date[9] - '0');
	}
	return 0;
}

void generate_dates(int * from_day, int * from_month, int * from_year, int * to_day, int * to_month, int * to_year)
{
	int x;
	int a_year[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int leap_year[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

}

int is_leap_year(int * year)
{
	if (*year % 4 == 0 && *year % 100 != 0 || *year % 400 == 0)
		return 1;
	else
		return 0;
}