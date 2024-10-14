#define MAX_LENGHT_OF_SEQUENCE 12
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int input(char* sequence, int* lenght_of_sequence) {
	if (fgets(sequence, MAX_LENGHT_OF_SEQUENCE, stdin) == NULL) {
		return 1;
	}

	*lenght_of_sequence = strlen(sequence) - 1;

	int stop = *lenght_of_sequence;

	for (int i = 0; i < stop; ++i) {
		for (int j = i + 1; j < stop + 1; ++j) {
			if (sequence[i] == sequence[j] || !isdigit(sequence[i])) {
				return 1;
			}
		}
	}

	return 0;
}

int output(char* sequence, int lenght_of_sequence) {
	int i = 0;
	while (i < lenght_of_sequence) {
		printf("%c", sequence[i]);
		++i;
	}
	printf("\n");
	return 0;
}
