#include "arithmetic.h"
#include <stdio.h>

static size_t compare(void *a, void *b)
{
    int _a = *(int *)a;
    int _b = *(int *)b;

    if (_a > _b)
    {
        return 1;
    }

    if (_a < _b)
    {
        return -1;
    }

    return 0;
}

void binary_search_test()
{
    puts("\nBinary Search Test Start\n");

    int data[100];
    int len = sizeof(data) / sizeof(data[0]);
    int target = 2;

    for (size_t i = 1; i <= 100; i++)
    {
        data[i - 1] = i;
    }


    size_t result = binary_search(data, len, sizeof(int), &target, compare);

    printf("\nBinary Search: result is %d\n", result);

    puts("\nBinary Search Test End\n");
}