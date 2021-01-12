/* 
	This is a program that investigates the size of types on my machine
	Aman Sawhney
	Jan. 4, 2020
*/


#include <stdio.h>

int main(void) {
	printf("an int is %lu btyes.\n", sizeof(int));
	printf("a double is %lu btyes.\n", sizeof(double));
	printf("a long is %lu btyes.\n", sizeof(long));
	printf("a float is %lu btyes.\n", sizeof(float));
	printf("a char is %lu btyes.\n", sizeof(char));
	printf("a long double is %lu btyes.\n", sizeof(long double));
	return 0;
}
