
int find_first_permutation_element(char* sequence, int lenght_of_sequence) {
	int i = lenght_of_sequence - 2;

	while (sequence[i] >= sequence[i + 1]) {
		--i;
		if (i == -1) {
			return -1;
		}
	}

	return i;
}

int find_second_permutation_element(char* sequence, int lenght_of_sequence, int i) {
	int j = lenght_of_sequence - 1;

	while ((sequence[i] >= sequence[j]) && j > i) {
		--j;
	}

	if (i == j)
		return -1;
	return j;
}

void swap_elements(char* sequence, int ind_first_element, int ind_second_element) {
	int tmp = sequence[ind_first_element];
	sequence[ind_first_element] = sequence[ind_second_element];
	sequence[ind_second_element] = tmp;
}

void reverse(char* sequence, int lenght_of_sequence, int start) {
	for (int j = 1; j < (((lenght_of_sequence - start) / 2) + 1); ++j) {
		swap_elements(sequence, start + j, lenght_of_sequence - j);
	}
}
