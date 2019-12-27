#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXISTS 1
#define NOT_EXISTS 0

typedef struct _TreeNode
{
    void *data;
    struct _TreeNode *left;
    struct _TreeNode *right;
} TreeNode;

typedef struct
{
    TreeNode *root;
    int size;
    int (*comparator)(void *, void *);
} TreeSet;

void treeset_add(TreeSet *treeSet, void *data);

void treeset_remove(TreeSet *treeSet, void *data, void (*destroyer)(void *));

int treeset_contains(TreeSet *treeSet, void *data);

void treeset_foreach(TreeSet *treeSet, void (*consumer)(void *));

void treeset_clean(TreeSet *treeSet, void (*destroyer)(void *));