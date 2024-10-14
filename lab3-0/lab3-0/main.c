#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "heap_sort.h"

int main(void) {
	int size, number;

	if (scanf("%d", &size) != 1) {
		printf("bad input");
		return 0;
	}

	int* arr = malloc(size * sizeof(int));
	if (!arr) {
		free(arr);
		return 0;
	}

	int i = 0;
	while (i < size) {
		if (scanf("%d", &number) != 1) {
			printf("bad input");
			free(arr);
			return 0;
		}
		arr[i] = number;

		++i;
	}

	heapSort(arr, size);

	i = 0;
	while (i < size) {
		printf("%d ", arr[i]);
		++i;
	}

	free(arr);
	return 0;
}