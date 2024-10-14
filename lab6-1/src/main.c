#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int size;
	if (scanf("%d", &size) != 1) {
		printf("input error");
		return 0;
	}

	if (size <= 0) {
		printf("0");
		return 0;
	}

	struct Node* tree = (struct Node*)malloc(size * sizeof(struct Node));
	if (!tree) {
		printf("memory error");
		free(tree);
		return 0;
	}

	int input;
	struct Node* root = NULL;
	for (int i = 0; i < size; ++i) {
		if (scanf("%d", &input) != 1) {
			printf("bad input");
			free(tree);
			return 0;
		}
		root = insert(root, tree, input, i);
	}
	root->col = 'B';
	printf("%d", height(root));
	free(tree);
	return 0;
}