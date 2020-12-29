#include <stdio.h>

int main(void) {
	double f, c;
	printf("Input the temp in f: ");
	scanf("%lf", &f);
	c = (f-32)/1.8;
	printf("\nThe temp is %lf degrees c \n", c);
}
