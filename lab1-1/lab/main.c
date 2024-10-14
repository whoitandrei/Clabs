#define _CRT_SECURE_NO_WARNINGS
#define BUFF_LEN 18

#include <stdio.h>
#include <string.h>
#include "func.h"


int main(void) {
	FILE* file = fopen("in.txt", "r");

	char sample[BUFF_LEN];

	if (fgets(sample, BUFF_LEN, file) == NULL) {
		printf("bad input");
		fclose(file);
		return 0;
	}

	rabinkarpsearch(file, sample);

	fclose(file);
	return 0;
}