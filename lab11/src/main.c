#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "knapsack.h"

void output(int result, int* added, int* weight, int* cost) {
    printf("%d\n", result);

    int i = 0;
    for (; added[i] >= 0; ++i)
        ;

    --i;
    for (; i >= 0; --i) {
        printf("%d %d\n", weight[added[i]], cost[added[i]]);
    }
}

int main() {
    int N;
    int W;

    if (!scanf("%d %d", &N, &W))
        return 0;

    int* weight = (int*)malloc(N * sizeof(int));
    int* cost = (int*)malloc(N * sizeof(int));

    
    for (int i = 0; i < N; i++) {
        if (!scanf("%d %d", &weight[i], &cost[i]))
            return 0;
    }

    int* added = (int*)malloc((N + 1) * sizeof(int));
    for (int i = 0; i < N + 1; ++i)
        added[i] = -1;

    int res = count(N, W, weight, cost, added); 
    output(res, added, weight, cost); 


    free(added);
    free(weight);
    free(cost);

    return 0;
}