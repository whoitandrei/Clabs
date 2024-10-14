#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"



static void make_parents(int* parent, int* rank, int size) {
	for (int i = 0; i < size + 1; ++i) {
		parent[i] = i;
		rank[i] = 1;
	}
}

static int find_parent(int* parent, int vertex) {
	if (parent[vertex] == vertex)
		return vertex;
	return find_parent(parent, parent[vertex]);
}

int cmp(const Edge* edge1, const Edge* edge2) {
	return edge1->cost - edge2->cost;
}

int kruskal(Edge* edges, int N, int M) {
	int* parent = calloc(N + 1, sizeof(int));
	int* rank = calloc(N + 1, sizeof(int));
	Edge* answer = (Edge*)malloc(N * sizeof(Edge));
	make_parents(parent, rank, N);

	qsort(edges, M, sizeof(Edge), (int (*)(const void*, const void*)) cmp);
	
	int i_ans = 0;
	int i = 0;
	int max_rank = 1;

	
	while (i < M && max_rank < N) {
		
		int head1 = find_parent(parent, edges[i].start);
		int head2 = find_parent(parent, edges[i].end);

		if (head1 != head2) {
			parent[head2] = head1;
			rank[head1] += rank[head2];
			max_rank = rank[head1];

			answer[i_ans++] = edges[i];
		}
		i++;
	}

	if (N != 0 && max_rank == N) {
		for (int j = 0; j < N - 1; ++j) {
			printf("%d %d\n", answer[j].start, answer[j].end);	
		}
		if (N > 1 && answer[N-1].cost == answer[N-2].cost)
			printf("%d %d\n", answer[N-1].start, answer[N-1].end);
	}
	else {
		printf("no spanning tree");
	}
	

	free(answer);
	free(parent);
	free(rank);
	
	return 0;
}