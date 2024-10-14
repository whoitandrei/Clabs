#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "kruskal.h"

int input_check(Edge* edge, int size, Edge* cur) {
    for (int i = 0; i < size; ++i) {
        if (edge[i].start == cur->start && edge[i].end == cur->end) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int N; // вершины
    if (!scanf("%d", &N) || N < 0) {
        printf("bad number of vertices");
        return 0;
    }

    int M; // ребра
    if (!scanf("%d", &M) || 0 > M || M > (N * (N - 1)) / 2) {
        printf("bad number of edges");
        return 0;
    }


    Edge* edges = (Edge*)malloc(sizeof(Edge) * M);

    for (int i = 0; i < M; ++i) {
        //добавляем ребро
        int start;
        int end;
        long long cost;
        if (scanf("%d %d %lld", &start, &end, &cost) != 3) {
            free(edges);
            printf("bad number of lines");
            return 0;
        }

        if (start < 0 || start > N || end < 0 || end > N) {
            free(edges);
            printf("bad vertex");
            return 0;
        }
        
        if (cost < 0 || cost > INT_MAX) {
            free(edges);
            printf("bad length");
            return 0;
        }
        
        edges[i].start = start;
        edges[i].end = end;
        edges[i].cost = (int)cost;
        if (input_check(edges, i, &edges[i])) {
            printf("bad number of edges");
            free(edges);
            return 0;
        }
    }

    kruskal(edges, N, M);
 

    free(edges);
    return EXIT_SUCCESS;
}
