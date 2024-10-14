#pragma once

struct st_Edge {
	int start;
	int end;
	int cost;
};
typedef struct st_Edge Edge;



int kruskal(Edge* edges, int N, int M);