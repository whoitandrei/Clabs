#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "graham.h"
#include <math.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1 || N < 0 || N > 100000) {
        printf("bad number of points");
        return 0;
    }

    point* grid = malloc(N * sizeof(point));
    for (int i = 0; i < N; ++i) {
        if (scanf("%d %d", &grid[i].x, &grid[i].y) != 2) {
            printf("bad number of lines");
            return 0;
        }
    }

    graham(grid, N);
    free(grid);
    return EXIT_SUCCESS;
}
