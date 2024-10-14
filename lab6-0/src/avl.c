#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int height(Node* node) {
    return node ? node->height : 0;
}

// dir=0 - right, dir=1 - left
Node* rotate(Node* root, int dir) {
    Node* tmp = root->link[1 - dir];
    root->link[1 - dir] = tmp->link[dir];
    tmp->link[dir] = root;
    root->height -= 2;
    return tmp;
}

Node* add(Node* tree, Node* root, int val, int i) {
    if (root != NULL) {
        if (val > root->value)
            root->link[1] = add(tree, root->link[1], val, i);
        else
            root->link[0] = add(tree, root->link[0], val, i);

        root->height = max(height(root->link[0]), height(root->link[1])) + 1;

        int hleft = height(root->link[0]);
        int hright = height(root->link[1]);

        if (hleft - hright > 1) {
            if ((height(root) - height(root->link[0]->link[1])) == 2) {
                root->link[0] = rotate(root->link[0], 0);
                root->link[0]->link[0]->height += 1;
                root = rotate(root, 1);
                root->height += 1;
            }
            else
                root = rotate(root, 1);
        }
        else if (hright - hleft > 1) {
            if ((height(root) - height(root->link[1]->link[0])) == 2) {
                root->link[1] = rotate(root->link[1], 1);
                root->link[1]->link[1]->height += 1;
                root = rotate(root, 0);
                root->height += 1;
            }
            else
                root = rotate(root, 0);
        }

    }
    else {
        tree[i].link[0] = NULL;
        tree[i].link[1] = NULL;
        tree[i].height = 1;
        tree[i].value = val;

        root = &tree[i];
    }
    return root;
}
