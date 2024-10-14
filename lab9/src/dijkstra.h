#pragma once
typedef struct st_data {
    char * used;
    int * parent;
    unsigned int* dist;
} Data;

int dijkstra(unsigned int** len, const int vertex, const int start, const int finish);

