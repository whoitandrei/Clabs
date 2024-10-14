#pragma once

struct Node {
	int val;
	char col;
	struct Node* link[2];
};

struct Node* insert(struct Node* root, struct Node* tree, int value, int i);
int height(struct Node* root);