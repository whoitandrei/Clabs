#include <stdio.h>
#include <stdlib.h>

void find_added(int* added, int** table, int* cost, int* weight, int res, int N, int W) {
    int index = 0;

    for (int i = N; i > 0 && res > 0; i--) {
        if (res != table[i - 1][W]) {
            added[index++] = i - 1;
            res -= cost[i - 1];
            W -= weight[i - 1];
        }
    }
}

int count(int N, int W, int* weight, int* cost, int* added) {

    int** table = (int**)malloc((N + 1) * sizeof(int*));
    for (int i = 0; i < N + 1; i++)
        table[i] = (int*)malloc((W + 1) * sizeof(int));

    for (int i = 0; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                table[i][w] = 0;
            }
            else if ((weight[i - 1] <= w) && ((cost[i - 1] + table[i - 1][w - weight[i - 1]]) > table[i - 1][w])) {
                table[i][w] = (cost[i - 1] + table[i - 1][w - weight[i - 1]]);
            }
            else {
                table[i][w] = table[i - 1][w];
            }
        }
    }

    int result = table[N][W];
    find_added(added, table, cost, weight, result, N, W);

    for (int i = 0; i < N + 1; i++) {
        free(table[i]);
    }
    free(table);

    return result;
}