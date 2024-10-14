#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "prima.h"

int input_error(int N, int M) {
	if (0 > N) {
		printf("bad number of vertices");
		return 1;
	}
	if (0 > M || (N * (N - 1) / 2) < M) {
		printf("bad number of edges");
		return 1;
	}
	return 0;
}

int bad_vertex(int v1, int v2, long long cost, int over) {
	if (v1 < 1 || v1 > over || v2 < 1 || v2 > over) {
		printf("bad vertex");
		return 1;
	}
	if (cost < 0 || cost > INT_MAX) {
		printf("bad length");
		return 1;
	}
	return 0;
}

void free_table(int** table, int size) {
	for (int i = 0; i < size; ++i) {
		free(table[i]);
	}
	free(table);
}

int main(void) {

	int** table;
	int vertex_size, edges_size;

	if (scanf("%d %d", &vertex_size, &edges_size) != 2) {
		printf("bad number of lines");
		return 0;
	}
	if (input_error(vertex_size, edges_size))
		return 0;

	table = malloc((vertex_size + 1) * sizeof(int*));
	if (table == NULL) {
		return 0;
	}

	for (int i = 0; i < vertex_size + 1; ++i) {
		table[i] = calloc(vertex_size + 1, sizeof(int));

		if (table[i] == NULL) {
			free_table(table, i);
			return 0;
		}

		for (int j = 0; j < vertex_size + 1; ++j)
			table[i][j] = 0;
	}

	int v1, v2;
	long long cost;
	for (int i = 0; i < edges_size; ++i) {
		if (scanf("%d %d %lld", &v1, &v2, &cost) != 3) {
			printf("bad number of lines");
			free_table(table, vertex_size);
			return 0;
		}
		if (bad_vertex(v1, v2, cost, vertex_size)) {
			free_table(table, vertex_size);
			return 0;
		}

		table[v1][v2] = (int)cost;
		table[v2][v1] = (int)cost;
	}

	prima(table, vertex_size + 1);
	free_table(table, vertex_size + 1);
	return 0;
}