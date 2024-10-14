#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "quick_sort.h"

int main(void) {
    int length;
    int* data;
    if (!scanf("%d", &length)) {
        return 0;
    }
    if (length == 0) {
        return 0;
    }
    
    if ((data = malloc(sizeof(int) * length))== NULL) {
        printf("ERROR MEMORY");
        return 0;
    }

    int i = 0;
    while (i < length) {
        if (!scanf("%d", &(data[i]))) {
            printf("bad input");
            free(data);
            return 0;
        }
        ++i;
    }

    quick_sort(data, length);

    i = 0;
    while (i < length) {
        printf("%d ", data[i]);
        ++i;
    }

    free(data);
    return 0;
}
