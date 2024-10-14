#define _CRT_SECURE_NO_WARNINGS
#include "topsort.h"
#include <stdio.h>
#include <stdlib.h>

int add(Stack* stack, int val) {
	if (stack->size >= STACK_MAX_SIZE) {
		return -1;
	}
	stack->data[stack->size++] = val;
	return 0;
}

int pop(Stack* stack) {
	if (stack->size <= 0) {
		return -1;
	}
	return stack->data[--stack->size];
}

static int dfs(char** table, Status* visited, Stack* stack, int vertex_size, const int v) {
	visited[v] = VISITING;
	for (int j = 0; j < vertex_size; ++j) {
		if (table[v][j]) {
			if (visited[j] == VISITING)
				return 1;
			if (!visited[j] && dfs(table, visited, stack, vertex_size, j)) {
				return 1;
			}
		}
	}
	visited[v] = VISITED;
	add(stack, v + 1);
	return 0;
}

void topsort(char** table, const int vertex_size, Stack* stack) {
	Status* visited = malloc(vertex_size * sizeof(Status));
	if (visited == NULL) {
		return;
	}
	
	for (int i = 0; i < vertex_size; ++i) {
		visited[i] = NOT_VISITED;
	}

	for (int i = 0; i < vertex_size; ++i) {
		if (!visited[i] && dfs(table, visited, stack, vertex_size, i)) {
			free(visited);
			printf("impossible to sort");
			return;
		}
	}
	free(visited);
}