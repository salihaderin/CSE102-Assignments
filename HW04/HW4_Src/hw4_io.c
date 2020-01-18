/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include <stdio.h>
#include "hw4_io.h"
int read_polynomial3(double * a0, double * a1, double * a2, double * a3);
int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4);
void write_polynomial3(double a0, double a1, double a2, double a3);
void write_polynomial4(double a0, double a1, double a2, double a3, double a4);

int read_polynomial3(double * a0, double * a1, double * a2, double * a3)
{
	double w, x, y, z;
	scanf("%lf", &w);
	scanf("%lf", &x);
	scanf("%lf", &y);
	scanf("%lf", &z);
	*a3 = w;
	*a2 = x;
	*a1 = y;
	*a0 = z;
}

int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4)
{
	double v, w, x, y, z;
	scanf("%lf", &v);
	scanf("%lf", &w);
	scanf("%lf", &x);
	scanf("%lf", &y);
	scanf("%lf", &z);
	*a4 = v;
	*a3 = w;
	*a2 = x;
	*a1 = y;
	*a0 = z;
}

int main(int argc, char const *argv[])
{
	double *a0, *a1, *a2, *a3;
	read_polynomial3(a0, a1, a2, a3);
	printf("%lf\n", *a0);
	return 0;
}