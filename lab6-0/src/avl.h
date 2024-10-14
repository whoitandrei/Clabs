#pragma once

typedef struct st_Node Node;
struct st_Node {
    int value;
    int height;
    struct st_Node* link[2];
};

int height(Node* node);
Node* add(Node* tree, Node* root, int val, int i);