#include <stdio.h>

#define PI 3.14159

int main() {
	double area = 0.0, radius = 0.0;
	printf("Input R: ");
	scanf("%lf", &radius);
	area = radius*radius*PI;
	printf("Your area is %lf \n", area);
	return 0;
}
