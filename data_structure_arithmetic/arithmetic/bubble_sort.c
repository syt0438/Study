#include "arithmetic.h"
#include "../utils/utils.h"

void bubble_sort(void *data, size_t len, size_t ele_size, int (*compare)(void *, void *))
{
    size_t unsorted_until_index = len - 1;
    int sorted = 0;

    if (len <= 1)
    {
        return;
    }

    while (!sorted)
    {
        sorted = 1;

        for (size_t i = 0; i < unsorted_until_index; i++)
        {
            void *a = ((char *)data) + (i * ele_size);
            void *b = ((char *)data) + ((i + 1) * ele_size);

            if (compare(a, b) > 0)
            {
                sorted = 0;

                swap(a, b, ele_size);
            }
        }

        unsorted_until_index--;
    }
}