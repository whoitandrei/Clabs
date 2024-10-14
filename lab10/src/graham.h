#pragma once

struct st_point {
	int x;
	int y;
	double angle;
};
typedef struct st_point point;

struct st_stack {
	point* added;
	size_t size;
};
typedef struct st_stack stack_t;

void graham(point* grid, int size);