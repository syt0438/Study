#include "arithmetic.h"
#include "../utils/utils.h"

void selection_sort(void *data, size_t len, size_t ele_size, int (*compare)(void *, void *))
{
    if (len <= 1)
    {
        return;
    }

    size_t start_idx = 0;
    size_t record_idx = start_idx;

    while (start_idx < len)
    {
        for (size_t i = start_idx + 1; i < len; ++i)
        {
            void *record = ((char *)data) + (record_idx * ele_size);
            void *curt = ((char *)data) + (i * ele_size);

            if (compare(record, curt) > 0)
            {
                record_idx = i;
            }
        }

        if (record_idx != start_idx)
        {
            void *a = ((char *)data) + (record_idx * ele_size);
            void *b = ((char *)data) + (start_idx * ele_size);

            swap(a, b, ele_size);
        }

        start_idx++;
        record_idx = start_idx;
    }
}