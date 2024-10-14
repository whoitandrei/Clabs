#define SHIFT_TABLE_SIZE 256

#include <stdio.h>

void create_shift_table(size_t* shift_table, unsigned char* pattern, size_t pattern_len) {
    for (size_t i = 0; i < SHIFT_TABLE_SIZE; i++) {
        shift_table[i] = pattern_len;
    }

    for (size_t i = 0; i < pattern_len - 1; i++) {
        shift_table[(size_t)pattern[i]] = pattern_len - 1 - i;
    }
}

size_t bm_search(const char* str, size_t str_len, const char* pattern, size_t pattern_len, size_t* shift_table, size_t global_pos) {
    size_t i = pattern_len;
    while (i <= str_len) {
        size_t k = pattern_len;
        size_t r = i;

        do {
            --k; --r;
            printf("%zu ", global_pos + r);
        } while (str[r] == pattern[k] && k > 0);
        i += shift_table[(unsigned char)str[i-1]];

    }
    return str_len + pattern_len - i;
}