#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MIDARR 499

static int char_to_int(char sym, int base) {
	int result = isdigit(sym) ?
		sym - '0' :
		(tolower(sym) - 'a' + 10);
	if (result < 0 || result >= base) {
		puts("bad input");
		exit(0);
	}
	return result;
}
static char int_to_char(int d) {
	return d < 10 ?
		d + '0' :
		(d - 10 + 'a');
}


static double from_b1_to_number(char* num, int b1) {
	int i = 0;
	double float_part = 0, delitel = b1, int_part = 0;
	int size = strlen(num) - 1;
	num[size] = '\0';
	if (num[i] == '.') {
		puts("bad input");
		exit(0);
	}
	while (isdigit(num[i]) || isalpha(num[i])) {
		int_part = int_part * b1 + char_to_int(num[i], b1);
		++i;
	}
	if (num[i] == '\0') {
		return int_part + float_part;
	}
	if ((num[i] == '.' && (!(isdigit(num[i + 1]) || isalpha(num[i + 1])))) || (num[i] != '.' && (isdigit(num[i + 1]) || isalpha(num[i + 1])))) {
		puts("bad input");
		exit(0);
	}	
	++i;
	while (num[i] != 0 && num[i] != '\n') {
		float_part = float_part + (char_to_int(num[i], b1) / delitel);
		delitel *= b1;
		i++;
	}
	return int_part + float_part;
}
static int from_number_to_b2(double number, int b2, char* result) {
	long long int_part = (long long)number;
	double float_part = number - int_part;
	int i = 1, ostatok, n = MIDARR;
	result[n] = '.';

	do {
		ostatok = int_part % b2;
		result[n - i] = int_to_char(ostatok);
		i++;
		int_part /= b2;
	} while (int_part > 0);
	if (float_part == 0) {
		result[n + 1] = '0';
		result[n + 2] = 0;
		return n - i + 1;
	}
	int j = 1;
	while (j < 13) {
		ostatok = float_part * b2;
		result[n + j] = int_to_char(ostatok);
		float_part = float_part * b2 - ostatok;
		++j;
	}
	result[n + j] = 0;
	return n - i + 1;

}

int translate(char* num, char* result, int b1, int b2) {
	double number = from_b1_to_number(num, b1);
	int shift = from_number_to_b2(number, b2, result);
	return shift;
}