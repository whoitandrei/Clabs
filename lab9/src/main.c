#define _CRT_SECURE_NO_WARNINGS
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int input_error(const int vertex_size, const int start, const int finish, const int edge_size) {
    if (vertex_size < 0 || vertex_size > 5000) {
        printf("bad number of vertices");
        return 1;
    }
    if (start < 1 || start > vertex_size || finish < 1 || finish > vertex_size) {
        printf("bad vertex_size");
        return 1;
    }
    if (edge_size < 0 || edge_size >((vertex_size * (vertex_size + 1)) / 2)) {
        printf("bad number of edges");
        return 1;
    }
    return 0;
}

int edge_error(const int vertex_size, const int edge_start, const int edge_end, const long long cost) {
    if (edge_start < 1 || edge_start > vertex_size || edge_end < 1 || edge_end > vertex_size) {
        printf("bad vertex_size");
        return 1;
    }
    if (cost <= 0 || cost > INT_MAX) {
        printf("bad length");
        return 1;
    }
    return 0;
}


void free_table(unsigned int** table, int size) {
    for (int i = 0; i < size; ++i) {
        free(table[i]);
    }
    free(table);
}

int main(void) {
    int vertex_size, start, finish, edge_size;
    if(scanf("%d %d %d %d", &vertex_size, &start, &finish, &edge_size) !=4 ){
        printf("bad number of lines");
        return 0;
    }
    if (input_error(vertex_size, start, finish, edge_size) == 1) {
        return 0;
    }

    int size = vertex_size + 1;
    unsigned int ** table = malloc(size * sizeof(unsigned int*));
    if(table == NULL){
        return 0;
    }
    
    for (int i = 0; i < size; ++i) {
        table[i] = malloc(size * sizeof(unsigned int));
        if (table[i] == NULL) {
            free_table(table, i + 1);
            return 0;
        }
        for (int j = 0; j < size; ++j)
            table[i][j] = UINT_MAX;
    }

    for (int i = 0; i < edge_size; i++) {
        int edge_start, edge_end;
        long long cost;
        
        if (scanf("%d %d %lld", &edge_start, &edge_end, &cost) != 3) {
            printf("bad number of lines");
            free_table(table, size);
            return 0;
        }
        if(edge_error(vertex_size, edge_start, edge_end, cost)==1){
            free_table(table, size);
            return 0;
        }
        
        table[edge_start][edge_end] = (unsigned int)cost;
        table[edge_end][edge_start] = (unsigned int)cost;
    }
    
    dijkstra(table, size, start, finish);
    free_table(table, size);
    
    return 0;
}
