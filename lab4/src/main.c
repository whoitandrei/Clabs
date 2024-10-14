#include <stdlib.h>
#include <stdio.h>
#include "func.h"


int main(void) {
    printf("calculator on C [whoitandrei, 2024]\n");

    char str[1005];
    if (fgets(str, 1002, stdin) == NULL) {
        printf("syntax error");
        return 0;
    }
    printf("\n");
    calculate(str);
    return EXIT_SUCCESS;
}
