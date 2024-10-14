#pragma once
#define STACK_MAX_SIZE 2000

typedef struct st_stack Stack;
struct st_stack {
	int data[STACK_MAX_SIZE];
	int size;
};

enum st_status {
	NOT_VISITED,
	VISITING,
	VISITED
};
typedef enum st_status Status;

void topsort(char** table, int vertex_size, Stack* stack);
int pop(Stack* stack);
