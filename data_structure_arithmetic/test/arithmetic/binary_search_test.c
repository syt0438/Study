#include "../../arithmetic/binary_search.h"
#include "binary_search_test.h"
#include <stdio.h>

size_t compare(void *a, void *b)
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

void test()
{
    int data[50];
    int len = sizeof(data) / sizeof(data[0]);
    int target = 88;

    for (size_t i = 1; i <= 50; i++)
    {
        data[i - 1] = i * 2;
        printf(" %d", i * 2);
    }

    size_t result = binary_search(data, len, sizeof(int), &target, compare);

    printf("\nBinary Search: result is %d\n", result);
}