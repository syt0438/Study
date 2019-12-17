#include "binary_search.h"

size_t binary_search(void *data, size_t len, size_t ele_size, void *item, size_t (*compare)(void *, void *))
{
    size_t lowerbound = 0;
    size_t upperbound = len - 1;

    while (lowerbound <= upperbound)
    {
        size_t mid_point = (lowerbound + upperbound) / 2;
        void *mid_point_addr = ((char *)data) + (mid_point * ele_size);

        int ret = compare(mid_point_addr, item);

        if (ret == 1)
        {
            upperbound = mid_point - 1;

            continue;
        }

        if (ret == -1)
        {
            lowerbound = mid_point + 1;

            continue;
        }

        return mid_point;
    }

    return NOT_FOUND;
}