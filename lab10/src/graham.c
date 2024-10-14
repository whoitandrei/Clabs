#include "graham.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculate_angle(point* grid, int size, int x0, int y0) {
	for (int i = 0; i < size; ++i) {
		grid[i].angle = atan2((double)grid[i].y - y0, (double)grid[i].x - x0);
	}
}

int f(double a) {
	if (a > 0)
		return 1;
	if (a < 0)
		return -1;
	return 0;
}


int cmp(const point* edge1, const point* edge2) {
	return f(edge1->angle - edge2->angle);
}

void endpush(stack_t* stack, point val) {
	stack->added[stack->size++] = val;
}

point endpop(stack_t* stack) {
	return stack->added[stack->size--];
}

point popprev(stack_t* stack) {
	point ans = stack->added[stack->size - 2];
	stack->added[stack->size - 2] = endpop(stack);
	return ans;
}

int abss(int a){
	return a >= 0 ? a : -a;
}

int sign(long long x) {
	return (x > 0) - (x < 0);
}

int orientation1(point A, point C, point B) {
	long long y_CA[2] = { ((long long)C.y - A.y) / INT_MAX, ((long long)C.y - A.y) % INT_MAX };
	long long y_BA[2] = { ((long long)B.y - A.y) / INT_MAX, ((long long)B.y - A.y) % INT_MAX };
	long long x_CA[2] = { ((long long)C.x - A.x) / INT_MAX, ((long long)C.x - A.x) % INT_MAX};
	long long x_BA[2] = { ((long long)B.x - A.x) / INT_MAX, ((long long)B.x - A.x) % INT_MAX};

	long long delta = x_CA[0] * y_BA[0] - y_CA[0] * x_BA[0];
	if (delta != 0) {
		return delta > 0 ? 1 : -1;
	}
	else {
		return 0;
	}
	
}

int orientation(point base, point frame, point new)
{	
	long double val = ((((long double)frame.x - base.x)) * (((long double)new.y - base.y))) - ((((long double)frame.y - base.y)) * (((long double)new.x - base.x)));
	
	if (val == 0) return 0;
	return (val > 0) ? 1 : -1;
}

int orientation2(point a, point c, point b) {
	int val1 = (b.y - a.y) - (c.y - b.y);

	if (val1 == 0) {
		if (b.x >= min(a.x, c.x) && b.x <= max(a.x, c.x))
			return 0;
		else
			return (b.x < min(a.x, c.x) ? 1 : 2);
	}
	else {
		if (b.y >= min(a.y, c.y) && b.y <= max(a.y, c.y))
			return 0;
		else
			return (b.y < min(a.y, c.y) ? 2 : 1);
	}
}

void graham(point* grid, int size) {
	point p0 = {
		.x = grid[0].x,
		.y = grid[0].y,
		.angle = 0.
	};

	for (int i = 1; i < size; ++i) {
		if (grid[i].y < p0.y || (grid[i].x > p0.x && grid[i].y == p0.y))
			p0 = grid[i];
	}

	calculate_angle(grid, size, p0.x, p0.y);
	qsort(grid, size, sizeof(point), (int (*)(const void*, const void*))cmp);

	stack_t stack = {
		.added = malloc(size * sizeof(point)),
		.size = 0
	};

	//printf("%d %d", grid[0].x, grid[0].y);
	for (int index = 0; index < size; ++index) {
		//const point cur = grid[index];
		//printf("%d %d %fcur\n", cur.x, cur.y, cur.angle);

		int do_not_add = 0;
		while (stack.size > 1) {
			//посчитать угол между двумя векторами последними
			//int delta = ((stack.added[stack.size - 1].x - stack.added[stack.size - 2].x) * (grid[index].y - stack.added[stack.size - 2].y) - \			((stack.added[stack.size - 1].y - stack.added[stack.size - 2].y) * (grid[index].x - stack.added[stack.size - 2].x)));
			int delta = orientation(stack.added[stack.size - 2], stack.added[stack.size - 1], grid[index]);
			if (delta < 0)
				endpop(&stack);
			else if (delta == 0) {
				if (abss(stack.added[stack.size - 1].x - stack.added[stack.size - 2].x) < abss(grid[index].x - stack.added[stack.size - 2].x))
					endpop(&stack);
				else if (abss(stack.added[stack.size - 1].y - stack.added[stack.size - 2].y) < abss(grid[index].y - stack.added[stack.size - 2].y))
					endpop(&stack);
				else {
					do_not_add = 1;
					break;
				}
			}
			else if (orientation(p0, stack.added[stack.size - 1], grid[index]) == 0) {
				if (abss(grid[index].x - p0.x) < abss(stack.added[stack.size - 1].x - p0.x))
					do_not_add = 1;
				else if (abss(grid[index].y - p0.y) < abss(stack.added[stack.size - 1].y - p0.y))
					do_not_add = 1;
				else {
					endpop(&stack);
					break;
				}
			}
			break;
		}

		if (!do_not_add)
			endpush(&stack, grid[index]);

	}

	for (int j = 0; j < stack.size; ++j) {
		printf("%d %d\n", stack.added[j].x, stack.added[j].y);
	}
}