#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int output(Data* par, const int size, const int start, const int finish, unsigned int** table) {
    for (int i = 1; i < size; i++) {
        if (par->used[i] == 0) {
            printf("oo ");
        }
        else {
            if (par->dist[i] <= INT_MAX) {
                printf("%u ", par->dist[i]);
            }
            else {
                printf("INT_MAX+ ");
            }
        }
    }
    printf("\n");
    if (par->used[finish] == 0) {
        printf("no path");
        return 0;
    }
    int maxCounter = 0;
    for (int i = 1; i < size; i++) {
        if (par->dist[i] >= INT_MAX && par->dist[i] != UINT_MAX) {
            maxCounter++;
        }
        else
            continue;
        
        for (int j = i; j < size; ++j) {
            if (table[i][j] > INT_MAX && table[i][j] != UINT_MAX) {
                maxCounter++;
            }
        }
    }
    if (maxCounter > 2 && par->dist[finish] > INT_MAX) {
        printf("overflow");
        return 0;
    }
    else {
        for (int from = finish; from != start; from = par->parent[from]) {
            printf("%d ", from);
        }
    }
    printf("%d", start);
    return 0;
}

int dijkstra(unsigned int** table, const int size, const int start, const int finish) {
    char* used = calloc(size, sizeof(char));
    if (used == NULL) {
        return 0;
    }
    unsigned int* dist = malloc(size * sizeof(unsigned int));
    if (dist == NULL) {
        free(used);
        return 0;
    }
    int* parent = malloc(size * sizeof(int));
    if (parent == NULL) {
        free(used);
        free(dist);
        return 0;
    }

    for (int i = 0; i < size; ++i) {
        dist[i] = table[start][i];
        parent[i] = start;
        used[i] = 0;
    }

    used[start] = 1;
    dist[start] = 0;
    
    for (int v = 1; v < size; ++v) {
        unsigned int mindist = UINT_MAX;
        int next = 0;
        for (int i = 1; i < size; ++i) {
            if (dist[i] < mindist && used[i] == 0) {
                mindist = dist[i];
                next = i;
            }
        }

        used[next] = 1;
        for (int i = 1; i < size; ++i) {
            if (used[i] == 0) {
                if (mindist < UINT_MAX && table[next][i] < UINT_MAX && mindist + table[next][i] < dist[i]) {
                    dist[i] = mindist + table[next][i];
                    parent[i] = next;
                }
            }
        }
    }

    Data data = {
        .dist = dist,
        .parent = parent,
        .used = used
    };

    output(&data, size, start, finish, table);
    free(used);
    free(dist);
    free(parent);
        
    return 0;
    
}