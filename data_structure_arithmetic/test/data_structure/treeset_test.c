#include "../../data_structure/treeset.h"
#include <stdio.h>

static void consumer(void *_data)
{
    long data = (long)_data;

    printf("%ld ", data);
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
    TreeSet set = {.comparator = comparator, .destroyer = destoryer};

    //#region init data
    treeset_add(&set, (void *)50);
    treeset_add(&set, (void *)25);
    treeset_add(&set, (void *)75);
    treeset_add(&set, (void *)10);
    treeset_add(&set, (void *)33);
    treeset_add(&set, (void *)4);
    treeset_add(&set, (void *)11);
    treeset_add(&set, (void *)30);
    treeset_add(&set, (void *)40);
    treeset_add(&set, (void *)56);
    treeset_add(&set, (void *)89);
    treeset_add(&set, (void *)52);
    treeset_add(&set, (void *)61);
    treeset_add(&set, (void *)82);
    treeset_add(&set, (void *)95);
    //#endregion

    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)4);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)10);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)56);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)50);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)75);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)25);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)61);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)82);
    treeset_foreach(&set, consumer);

    treeset_remove(&set, (void *)30);
    treeset_foreach(&set, consumer);

    treeset_clean(&set);
}