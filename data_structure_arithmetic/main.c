#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include "test/arithmetic/arithmetic.h"
#include "test/data_structure/data_structure.h"

int main()
{
    // bubble_sort_test();
    // selection_sort_test();
    // insertion_sort_test();
    // quick_sort_partition_test();
    // quick_sort_test();
    // quick_select_test();

    select();

    treeset_test();

    return EXIT_SUCCESS;
}