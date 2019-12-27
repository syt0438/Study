#include "../../data_structure/treeset.h"
#include <stdio.h>

static void consumer(void *_data)
{
    long data = (long)_data;

    printf("%ld\n", data);
}

static int comparator(void *_a, void *_b)
{
    long a = (long)_a;
    long b = (long)_b;

    return a - b;
}

static void destoryer(void *_data)
{
    long data = (long)_data;

    printf("Destory data: %ld\n", data);
}

void treeset_test()
{
    TreeSet set = {.comparator = comparator};

    //#region init data
    treeset_add(&set, (void *)50);
    treeset_add(&set, (void *)25);
    treeset_add(&set, (void *)75);
    treeset_add(&set, (void *)11);
    treeset_add(&set, (void *)33);
    treeset_add(&set, (void *)30);
    treeset_add(&set, (void *)40);
    treeset_add(&set, (void *)56);
    treeset_add(&set, (void *)89);
    treeset_add(&set, (void *)52);
    treeset_add(&set, (void *)61);
    treeset_add(&set, (void *)82);
    treeset_add(&set, (void *)95);
    //#endregion

    treeset_remove(&set, (void *)11, destoryer);
    treeset_remove(&set, (void *)56, destoryer);
    treeset_remove(&set, (void *)50, destoryer);

    printf("\n\nClean before node count: %d\n\n", set.size);

    treeset_foreach(&set, consumer);

    treeset_clean(&set, destoryer);

    printf("\n\nClean after node count: %d\n\n", set.size);

    treeset_foreach(&set, consumer);
}