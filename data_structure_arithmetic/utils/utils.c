#include "utils.h"

void swap(void *a, void *b, size_t ele_size)
{
    while (ele_size > 0)
    {
        ele_size--;

        *((char *)a + ele_size) ^= *((char *)b + ele_size);
        *((char *)b + ele_size) ^= *((char *)a + ele_size);
        *((char *)a + ele_size) ^= *((char *)b + ele_size);
    }
}
