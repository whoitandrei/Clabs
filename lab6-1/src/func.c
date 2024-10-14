#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int maxx(int a, int b) {
	return a > b ? a : b;
}

int is_black(struct Node* root) {
	return (root->col == 'B') ? 1 : 0;
}

int height(struct Node* root) {
	if (root == NULL) {
		return 1;
	}
	else {
		int leftHeight = height(root->link[0]);
		int rightHeight = height(root->link[1]);

		return maxx(leftHeight, rightHeight) + is_black(root);
	}
}

char recol(struct Node* root) {
	return (root->col == 'R') ? 'B' : 'R';
}

void change_color(struct Node* root) {
	root->col = recol(root);
	root->link[0]->col = recol(root->link[0]);
	root->link[1]->col = recol(root->link[1]);
}


static struct Node* rotate(struct Node* root, int dir) {
	struct Node* tmp = root->link[1 - dir];
	root->link[dir] = tmp->link[1 - dir];
	tmp->link[1 - dir] = root;
	tmp->col = root->col;
	root->col = 'R';
	return tmp;
}

static struct Node* big_rotate(struct Node* root, int dir) {
	root->link[dir] = rotate(root->link[dir], dir);
	return rotate(root, 1 - dir);
}


struct Node* fix(struct Node* root, int dir) {
	if ((root->link[dir]->link[dir] == NULL && root->link[dir]->link[!dir] == NULL)) {
		return root;
	}

	if (root->link[dir]->col == 'R') {
		if (root->link[!dir] != NULL && root->link[!dir]->col == 'R') {
			if ((root->link[dir]->link[0] != NULL && root->link[dir]->link[0]->col == 'R') ||
				(root->link[dir]->link[1] != NULL && root->link[dir]->link[1]->col == 'R')) {
				change_color(root);
			}
		}
		else {
			if (root->link[dir]->link[dir] != NULL && root->link[dir]->link[dir]->col == 'R') {
				root = rotate(root, 1 - dir);
			}
			else if (root->link[dir]->link[!dir] != NULL && root->link[dir]->link[!dir]->col == 'R') {
				root = big_rotate(root, 1 - dir);
			}
		}
	}
	return root;
}


struct Node* insert(struct Node* root, struct Node* tree, int value, int i) {
	if (root == NULL) {
		tree[i].val = value;
		tree[i].col = 'R';
		tree[i].link[0] = NULL;
		tree[i].link[1] = NULL;

		root = &tree[i];
		return root;
	}

	if (value > root->val) {
		root->link[1] = insert(root->link[1], tree, value, i);
		return fix(root, 1);
	}

	root->link[0] = insert(root->link[0], tree, value, i);
	return fix(root, 0);

}
