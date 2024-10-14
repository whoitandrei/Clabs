#define MAX_LENGHT_OF_SEQUENCE 12
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "in_out.h"
#include "func.h"


int main(void) {
	char sequence[MAX_LENGHT_OF_SEQUENCE];
	int lenght_of_sequence;
	int permutations_number;

	if (input(sequence, &lenght_of_sequence) || scanf("%d", &permutations_number) != 1) {
		printf("bad input");
		return 0;
	}
	
	int ind_first_element;
	int permutations_done = 0;
	while ((ind_first_element = find_first_permutation_element(sequence, lenght_of_sequence)) != -1 \
		&& permutations_number != permutations_done)
	{
		int ind_sesond_element = find_second_permutation_element(sequence, lenght_of_sequence, ind_first_element);
		swap_elements(sequence, ind_first_element, ind_sesond_element);
		reverse(sequence, lenght_of_sequence, ind_first_element);
		output(sequence, lenght_of_sequence);

		permutations_done += 1;
	}

	return 0;
}

