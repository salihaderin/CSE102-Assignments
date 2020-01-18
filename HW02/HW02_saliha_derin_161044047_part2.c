#include <stdio.h>
int firstDigit(long int num);
int secondDigit(long int num);
int thirdDigit(long int num);
int fourthDigit(long int num);
int fifthDigit(long int num);
int main()
{
	long int number;
	int first, second, third, fourth, fifth;
	printf("Enter the number: ");
	scanf("%ld", &number);
	if(number < 23 || number > 98760){
		printf("You cannot enter this number.\n");
	}
	if(number > 9999){
		fifth = fifthDigit(number);
		printf("The fifth digit is %d\n", fifth);
	}
	if(number > 999){
		fourth = fourthDigit(number);
		printf("The fourth digit is %d\n", fourth);
	}
	if(number > 99){
		third = thirdDigit(number);
		printf("The third digit is %d\n", third);
	}
	second = secondDigit(number);
	printf("The second digit is %d\n", second);
	first = firstDigit(number);
	printf("The first digit is %d\n", first);

	return 0;
}

int firstDigit(long int num)
{
	int digit;
	digit = num % 10;
	return digit;
}

int secondDigit(long int num)
{
	int digit;
	digit = num % 100;
	if(digit < 10)
		digit = 0;
	else
		digit = (digit - firstDigit(num)) / 10;
	return digit;
}

int thirdDigit(long int num)
{
	int digit;
	digit = num % 1000;
	if(digit < 100)
		digit = 0;
	else
		digit = (digit - (num % 100)) / 100;
	return digit;
}

int fourthDigit(long int num)
{
	int digit;
	digit = num % 10000;
	if(digit < 1000)
		digit = 0;
	else
		digit = (digit - (num % 1000)) / 1000;
	return digit;
}

int fifthDigit(long int num)
{
	int digit;
	digit = num / 10000;
	return digit;
}
