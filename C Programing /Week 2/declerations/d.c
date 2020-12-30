/*
	This is a program to explore declarations. It will average 3 numbers
	Aman Sawhney	
	12/30/20
*/

#include <stdio.h>

int main(void) {
	int a = 1, b = 2, c = 5; //declaring my integers to be averaged
	double average = 0.0;
	average = (a+b+c)/3.0;
	printf("The avg of %d, %d, and %d is %lf\n", a, b, c, average); 
	return 0;
}
