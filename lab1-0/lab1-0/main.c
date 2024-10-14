#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "func.h"

#define SHIFT_TABLE_SIZE 256
#define MAX_PATTERN_SIZE 18
#define BUFF_LEN 9999

int main(void) {
	FILE* file = fopen("in.txt", "r");
	char pattern[MAX_PATTERN_SIZE];
	if (fgets(pattern, MAX_PATTERN_SIZE, file) == NULL) {
		printf("bad input");
		fclose(file);
		return 0;
	}
	size_t pattern_len = strlen(pattern) - 1;
	size_t shift_table[SHIFT_TABLE_SIZE] = { 0 };

	create_shift_table(shift_table, pattern, pattern_len);

	char str[BUFF_LEN];
	size_t read_len = 0, tail_len = 0, global_pos = 1;
	while ((read_len = fread(str + tail_len, 1, BUFF_LEN - tail_len, file)) > 0) {
		size_t str_len = read_len + tail_len;
		tail_len = bm_search(str, str_len, pattern, pattern_len, shift_table, global_pos);
		size_t used_len = str_len - tail_len;
		memmove(str, str + used_len, tail_len);
		global_pos += used_len;

	}
	fclose(file);

	return 0;
}