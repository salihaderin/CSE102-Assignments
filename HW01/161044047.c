#include <stdio.h>
#include <math.h>
#define PI 3.141592
double circle_area(double radius);
double calc_hypotenuse(int side1, int side2);
double calc_radius_of_smallest_circle(int side1, int side2);
double calc_radius_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_circle(int side1, int side2);
double calc_area_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_square(int side1, int side2);
double calc_area_of_largest_square(int side1, int side2);
double calc_area_of_square (int side);
void display_results(double largest_circle, double largest_square, double smallest_circle, double smallest_square);
/*
 *main fonksiyonunda degiskenleri tanimlayip fonksiyonlarimi cagirdim.
 */
int main()
{
	int side1, side2;
	double largest_circle, largest_square, smallest_circle, smallest_square;
	printf("Enter the first side of rectangle:");
	scanf("%d", &side1);
	printf("Enter the second side of rectangle:");
	scanf("%d", &side2);
	largest_circle = calc_area_of_largest_circle(side1, side2);
	smallest_circle =  calc_area_of_smallest_circle(side1, side2);
	largest_square = calc_area_of_largest_square(side1, side2);
	smallest_square = calc_area_of_smallest_square(side1, side2);
	display_results(largest_circle, largest_square, smallest_circle, smallest_square);
	return 0;
}

double circle_area(double radius)
{
	double area = PI*(pow(radius, 2));
	return area;
}

double calc_hypotenuse(int side1, int side2)
{
	double hypo;
	hypo = sqrt(pow(side1,2) + pow(side2, 2));
	return hypo;
}

double calc_area_of_square (int side)
{
	double area = pow((double)side, 2);
	return area;
}

double calc_radius_of_smallest_circle(int side1, int side2)
{
	double radiusOfSmallestCircle;
	if(side1 > side2){
		radiusOfSmallestCircle = (double)side2/2.0;
	}
	else
		radiusOfSmallestCircle = (double)side1/2.0;

	return radiusOfSmallestCircle;
}

double calc_radius_of_largest_circle(int side1, int side2)
{
	double radiusOfLargestCircle;
	radiusOfLargestCircle = sqrt(pow((double)side1/2.0, 2) + pow((double)side2/2.0, 2));
	return radiusOfLargestCircle;
}

double calc_area_of_smallest_circle(int side1, int side2)
{
	double radius = calc_radius_of_largest_circle(side1, side2);
	double area = circle_area(radius);
	return area;
}

double calc_area_of_largest_circle(int side1, int side2)
{
	double radius = calc_radius_of_smallest_circle(side1, side2);
	double area = circle_area(radius);
	return area;
}

double calc_area_of_smallest_square(int side1, int side2)
{
	double area;
	int side;
	if(side1 > side2){
		side = side1;
	}
	else
		side = side2;

	area = calc_area_of_square(side);
	return area;
}

double calc_area_of_largest_square(int side1, int side2)
{
	double area;
	int side;
	if(side1 < side2){
		side = side1;
	}
	else
		side = side2;

	area = calc_area_of_square(side);
	return area;
}

void display_results(double largest_circle, double largest_square, double smallest_circle, double smallest_square)
{
	printf("The area of the largest circle that fits inside a rectangle:\t\t%.2lf\n", largest_circle);
	printf("The area of the largest square that fits inside a rectangle:\t\t%.2lf\n", largest_square);
	printf("The area of the smallest circle that surrounds the same rectangle:\t%.2lf\n", smallest_circle);
	printf("The area of the smallest square that surrounds the same rectangle\t%.2lf\n", smallest_square);
}
