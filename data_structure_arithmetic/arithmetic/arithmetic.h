#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOT_FOUND -1

int binary_search(void *data, size_t len, size_t ele_size, void *item, int (*compare)(void *, void *));

void bubble_sort(void *data, size_t len, size_t ele_size, int (*compare)(void *, void *));

void selection_sort(void *data, size_t len, size_t ele_size, int (*compare)(void *, void *));

void insertion_sort(void *data, size_t len, size_t ele_size, int (*compare)(void *, void *));

int partition(void *data, int left_idx, int right_idx, size_t ele_size, int (*compare)(void *, void *));

void quick_sort(void *data, int left_idx, int right_idx, size_t ele_size, int (*compare)(void *, void *));

int quick_select(void *data, int left_idx, int right_idx, size_t ele_size, int kth_lowest, int (*compare)(void *, void *));