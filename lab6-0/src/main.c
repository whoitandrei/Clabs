#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int main(void) {
    FILE* file;
    file = fopen("in.txt", "r");
    if (!file) {
        printf("input file error");
        return 0;
    }

    int size;
    if (fscanf(file, "%d", &size) != 1) {
        printf("bad size input: %d", size);
        return 0;
    }

    if (size < 0) {
        printf("0");
        return EXIT_SUCCESS;
    }

    Node* tree = malloc(sizeof(Node) * size);
    Node* root = NULL;
    for (int i = 0; i < size; i++) {
        int val;
        if (fscanf(file, "%d", &val) != 1) 
            return 0;
        root = add(tree, root, val, i);
    }

    printf("%d", height(root));
    free(tree);
    fclose(file);
    return EXIT_SUCCESS;
}