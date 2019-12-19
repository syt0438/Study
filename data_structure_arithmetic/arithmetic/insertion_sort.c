#include "arithmetic.h"
#include "../utils/utils.h"

void insertion_sort(void *data, size_t len, size_t ele_size, int (*compare)(void *, void *))
{
    if (len <= 1)
    {
        return;
    }

    int insert_idx = 1;
    int cursor_idx = insert_idx;

    void *insert_tmp = malloc(ele_size);
    while (insert_idx < len)
    {
        memcpy(insert_tmp, ((char *)data) + (insert_idx * ele_size), ele_size);

        char *cursor = NULL;
        void *empty = NULL;

        while (--cursor_idx >= 0)
        {
            cursor = ((char *)data) + (cursor_idx * ele_size);
            empty = cursor + (1 * ele_size);

            if (compare(cursor, insert_tmp) > 0)
            {
                swap(cursor, empty, ele_size);
            }
            else
            {
                swap(insert_tmp, empty, ele_size);

                break;
            }
        }

        insert_idx++;
        cursor_idx = insert_idx;
    }

    free(insert_tmp);
}
