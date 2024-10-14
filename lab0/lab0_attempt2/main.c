#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include "func.h"
#define STRLEN 16
#define RESULTLEN 1000


int main(void) {
	int b1, b2, shift;
	if (scanf("%d %d\n", &b1, &b2) != 2 || b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16) {
		puts("bad input");
		return 0;
	}
	char num[STRLEN];
	char result[RESULTLEN];
	if (NULL == fgets(num, STRLEN, stdin)) {
		puts("bad input");
		return 0;
	}
	shift = translate(num, result, b1, b2);
	printf("%s", result + shift);
	return 0;
}
