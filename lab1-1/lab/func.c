#include <stdio.h>
#include <string.h>

#define STR_SIZE 20

static unsigned int make_hash(const char* str, size_t str_len, int* pow3)
{
    size_t hash = 0;
    size_t power = 1;

    for (int i = 0; i < (int)str_len; i++)
    {
        hash += ((unsigned char)str[i] % 3) * power;
        power *= 3;
    }

    *pow3 = power;
    return hash;
}

static int rk_search(const char* str, size_t str_len, const char* sample, size_t sample_len, unsigned int sample_hash, size_t index) {
    if (str_len < sample_len) {
        return 0;
    }
    int pow3 = 0;
    unsigned int str_hash = make_hash(str, sample_len, &pow3);
    size_t i = 0;
    while (i < str_len - sample_len + 1) {
        if (str_hash == sample_hash) {
            for (size_t j = 0; j < sample_len; ++j) {
                printf("%zu ", index + i + j);
                if (str[i + j] != sample[j]) {
                    break;
                }
            }
        }
        if (i + sample_len < str_len) {
            str_hash = ((str_hash - ((unsigned char)str[i] % 3)) + ((unsigned char)str[i + sample_len] % 3) * pow3) / 3;
        }

        ++i;


    }
    return 0;
}


void rabinkarpsearch(FILE* file, const char* sample) {
    size_t sample_len = strlen(sample) - 1;
    size_t index = 1, offset = 0, read_len;
    int pow3 = 0;
    unsigned int sample_hash = make_hash(sample, sample_len, &pow3);
    printf("%u ", sample_hash);

    char str[STR_SIZE];
    while ((read_len = fread(str + offset, sizeof(char), STR_SIZE - offset, file)) > 0) {
        size_t str_len = read_len + offset;
        rk_search(str, str_len, sample, sample_len, sample_hash, index);
        offset = sample_len - 1;
        if (str_len > offset) {
            memmove(str, str + str_len - sample_len + 1, offset);
        }
        index += str_len - offset;
    }
}

