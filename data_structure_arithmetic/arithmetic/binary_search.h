#include <stdlib.h>
#define NOT_FOUND -1

size_t binary_search(void *data, size_t len, size_t ele_size, void *item, size_t (*compare)(void *, void *));