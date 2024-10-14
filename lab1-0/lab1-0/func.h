#pragma once

void create_shift_table(size_t* shift_table, unsigned char* pattern, size_t pattern_size);
size_t bm_search(const char* str, size_t str_len, const char* pattern, size_t pattern_len, size_t* shift_table, size_t global_pos);
