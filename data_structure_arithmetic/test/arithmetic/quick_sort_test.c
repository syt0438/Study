#include "arithmetic.h"
#include "../../arithmetic/arithmetic.h"

static int compare(void *a, void *b)
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

void quick_sort_partition_test()
{
    puts("\nQuick Sort Partition Start\n");

    int data[] = {65, 55, 45, 10, 25, 15, 35};
    // int data[] = {3, 1, 3};
    // int data[] = {10, 15, 25};
    // int data[] = {15, 10};
    // int data[] = {10};
    int len = sizeof(data) / sizeof(data[0]);

    partition(data, 0, len - 1, sizeof(int), compare);

    printf("Partitioned Data: \n");

    for (int i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }

    puts("");
    puts("\nQuick Sort Partition End\n");
}

void quick_sort_test()
{
    puts("\nQuick Sort Start\n");

    // int data[] = {65, 55, 45, 10, 25, 15, 35};
    // int data[] = {3, 1, 3};
    int data[] = {25, 15, 10};
    // int data[] = {15, 10};
    // int data[] = {10};
    int len = sizeof(data) / sizeof(data[0]);

    quick_sort(data, 0, len - 1, sizeof(int), compare);

    printf("Sort Data: \n");

    for (int i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }

    puts("");
    puts("\nQuick Sort End\n");
}