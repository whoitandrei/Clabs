#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(void) {
    Data in = {
        .bitpos = 0,
        .pos = 0,
        .size = 0,
    };

    in.file = fopen("in.txt", "rb");
    if (in.file == NULL) {
        fclose(in.file);
        return 0;
    }


    if (!(in.size = fread(in.buffer, 1, BUFFER_SIZE, in.file))) {
        fclose(in.file);
        return 0;
    }

    int status = in.buffer[in.pos++];
    if (status == 'c') {
        encode(&in);
    }
    else if (status == 'd')
        decode(&in);

    fclose(in.file);
    return EXIT_SUCCESS;
}



