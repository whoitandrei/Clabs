#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "prima.h"


int find_shortest(unsigned int* shortest, char* visited, int size) {
	unsigned int min = UINT_MAX;
	int shortest_ind = 0;
	for (int i = 1; i < size; ++i) {
		if (!visited[i] && shortest[i] < min) {
			min = shortest[i];
			shortest_ind = i;
		}
	}
	return shortest_ind;
}

char connected(int* parent, int size) {
	for (int i = 1; i < size; ++i) {
		if (!parent[i])
			return 0;
	}
	return 1;
}

void prima(int** table, int size) {
	char* visited = malloc(size * sizeof(char));
	if (visited == NULL)
		return;

	unsigned int* shortest = malloc(size * sizeof(unsigned int));
	if (shortest == NULL) {
		free(visited);
		return;
	}

	int* parent = malloc(size * sizeof(int));
	if (parent == NULL) {
		free(visited);
		free(shortest);
		return;
	}

	for (int i = 0; i < size; ++i) {
		shortest[i] = UINT_MAX;
		visited[i] = 0;
		parent[i] = 0;
	}
	if (size > 1) {
		shortest[1] = 0;
		parent[1] = 1;
	}

	for (int i = 1; i < size - 1; ++i) {
		int shortest_ind = find_shortest(shortest, visited, size);
		visited[shortest_ind] = 1;

		for (int v = 1; v < size; ++v) {
			if (table[shortest_ind][v] > 0 && !visited[v] && (unsigned int)table[shortest_ind][v] < shortest[v]) {
				parent[v] = shortest_ind;
				shortest[v] = (unsigned int)table[shortest_ind][v];
			}
		}
	}


	if (size > 1 && connected(parent, size)) {
		for (int i = 2; i < size; i++)
			printf("%d %d\n", parent[i], i);
	}
	else
		printf("no spanning tree");

	free(visited);
	free(parent);
	free(shortest);
}


