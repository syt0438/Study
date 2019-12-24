#include "arithmetic.h"
#include "../utils/utils.h"

int quick_select(void *data, int left_idx, int right_idx, size_t ele_size, int kth_lowest, int (*compare)(void *, void *))
{
    if (left_idx >= right_idx)
    {
        return left_idx;
    }

    int kth_lowest_actual = kth_lowest - 1;

    int pivot_idx = partition(data, left_idx, right_idx, ele_size, compare);

    if (pivot_idx > kth_lowest_actual)
    {
        return quick_select(data, left_idx, pivot_idx - 1, ele_size, kth_lowest, compare);
    }
    else if (pivot_idx < kth_lowest_actual)
    {
        return quick_select(data, pivot_idx + 1, right_idx, ele_size, kth_lowest, compare);
    }
    else
    {
        return pivot_idx;
    }
}