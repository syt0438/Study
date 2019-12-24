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

// static int data[] = {65, 55, 45, 10, 25, 15, 35};
static int data[] = {0, 5, 2, 1, 6, 3};
// static int data[] = {3, 1, 3};
// static int data[] = {25, 15, 10};
// static int data[] = {15, 10};
// static int data[] = {10};
static int len = sizeof(data) / sizeof(data[0]);

void quick_select_test()
{
    puts("\nQuick Select Start\n");

    int kth_lowest = quick_select(data, 0, len - 1, sizeof(int), 1, compare);

    printf("Sort Data: \n");

    for (int i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }

    puts("");

    if (kth_lowest != -1)
    {
        printf("Select Data: %d\n", data[kth_lowest]);
    }
    else
    {
        printf("Not Found!\n");
    }

    puts("");
    puts("\nQuick Select End\n");
}