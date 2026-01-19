#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

size_t get_max_prime(size_t max_value);
size_t hash1(size_t size, int num);
size_t hash2(size_t size, int num);
size_t hash(size_t size, int num, int idx);

#endif
