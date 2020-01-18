/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/
#include <stdio.h>
#include "hw4_lib.h"

double integral(double f(double x), double xs, double xe, double delta);
double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta);
int derivatives(double f(double a), double x, double eps, double * d1, double * d2);
int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2);
int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4);

/*
 *pdfte verdiginiz gibi turevleri hesapladim
 */
int derivatives(double f(double a), double x, double eps, double * d1, double * d2){
	*d1 = (f(x + eps) - f(x - eps)) / 2 * eps;
	*d2 = (f(x + eps) - 2 * f(x) + f(x - eps)) / (eps * eps);
	if(eps == 0)
		return -1;
	else
		return 1;
}

int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2)
{
	double d3, d4, d5, d6, e3, e4, forabs1, forabs2;
	d5 = (f(x + eps) - f(x - eps)) / 2 * eps;
	d6 = (f(x + eps) - 2 * f(x) + f(x - eps)) / (eps * eps);
	d3 = (d1(x + eps) - d1(x - eps)) / 2 * eps;
	d4 = (d2(x + eps) - 2 * d2(x) + d2(x - eps)) / (eps * eps);
	forabs1 = d3 - d5;
	forabs2 = d4 - d6;
	*e1 = fabs(forabs1);
	*e2 = fabs(forabs2);
	if(eps == 0)
		return -1;
	else
		return 1;
}

double integral(double f(double x), double xs, double xe, double delta)
{
	double dx, s;
	int i;
	dx = (xe - xs) / delta;
	s = (f(xe) + f(xs)) / 2;
	for(i = 1; i < delta; ++i){
		s += f(xs + i * dx);
	}
	return s * dx;
}

double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta)
{
	double integral, dx, s, dy, t;
	int i, j;
	dx = (xe - xs) / delta;
	s = (f(xe, ye) + f(xs, ys)) / 2;
	for(i = 1; i < delta; ++i){
		s += f(xs + i * dx, ys + i * dy);
	}
	integral = (s * dx) + (s * dy);
	return integral;
}