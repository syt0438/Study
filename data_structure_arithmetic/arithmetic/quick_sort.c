#include "arithmetic.h"
#include "../utils/utils.h"

int partition(void *data, int left_idx, int right_idx, size_t ele_size, int (*compare)(void *, void *))
{
    if (left_idx >= right_idx)
    {
        return left_idx;
    }

    int pivot_idx = right_idx--;

    void *left = ((char *)data) + (left_idx * ele_size);
    void *right = ((char *)data) + (right_idx * ele_size);
    void *pivot = ((char *)data) + (pivot_idx * ele_size);

    for (;;)
    {
        for (;;)
        {
            if (compare(left, pivot) >= 0)
            {
                break;
            }

            left = ((char *)data) + (++left_idx * ele_size);
        }

        for (;;)
        {
            if (compare(right, pivot) <= 0)
            {
                break;
            }

            if (right_idx == 0)
            {
                break;
            }

            right = ((char *)data) + (--right_idx * ele_size);
        }

        if (left_idx >= right_idx)
        {
            break;
        }

        swap(left, right, ele_size);
    }

    if (left_idx != pivot_idx)
    {
        swap(left, pivot, ele_size);
    }

    return left_idx;
}

void quick_sort(void *data, int left_idx, int right_idx, size_t ele_size, int (*compare)(void *, void *))
{
    if (left_idx >= right_idx)
    {
        return;
    }

    int pivot_idx = partition(data, left_idx, right_idx, ele_size, compare);

    quick_sort(data, left_idx, pivot_idx - 1, ele_size, compare);
    quick_sort(data, pivot_idx + 1, right_idx, ele_size, compare);
}