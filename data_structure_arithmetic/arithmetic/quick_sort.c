#include "arithmetic.h"
#include "../utils/utils.h"

static int count = 0;

int partition(void *data, int left_idx, int right_idx, size_t ele_size, int (*compare)(void *, void *))
{
    printf("Partition count: %d\n", ++count);

    if (left_idx >= right_idx)
    {
        return left_idx;
    }

    int pivot_idx = right_idx--;
    void *left, *right;
    void *pivot = ((char *)data) + (pivot_idx * ele_size);

    for (;;)
    {
        for (;;)
        {
            left = ((char *)data) + (left_idx * ele_size);

            if (compare(left, pivot) >= 0)
            {
                break;
            }

            left_idx++;
        }

        for (;;)
        {
            right = ((char *)data) + (right_idx * ele_size);

            if (compare(right, pivot) <= 0 || right_idx <= 0)
            {
                break;
            }

            right_idx--;
        }

        if (left_idx >= right_idx)
        {
            break;
        }

        swap(left, right, ele_size);
    }

    if (left_idx < pivot_idx)
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
