#include "arithmetic.h"
#include <stdio.h>

static size_t compare(void *a, void *b)
{
    int _a = *(int *)a;
    int _b = *(int *)b;

    if (_a < _b)
    {
        return 1;
    }
    
    return 0;
}

void bubble_sort_test()
{
    puts("\nBubble Sort Start\n");

    int data[] = {65, 55, 45, 10, 25, 15, 35};
    int len = sizeof(data) / sizeof(data[0]);

    bubble_sort(data, len, sizeof(int), compare);

    printf("Sorted data: \n");

    for (int i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }

    puts("\nBubble Sort End\n");
}