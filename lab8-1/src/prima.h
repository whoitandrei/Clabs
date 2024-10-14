#pragma once
#define INFINITIVE INT_MAX + 1

struct st_edge {
    int start;
    int end;
    int cost;
};
typedef struct st_edge edge;

struct st_ans {
    edge* data;
    int size;
};
typedef struct st_ans Answer;

void prima(int** table, int vertex_size);