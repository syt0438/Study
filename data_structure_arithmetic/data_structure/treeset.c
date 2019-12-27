#include "treeset.h"

static void treeset_insert(TreeNode *node, TreeNode *new_node, int (*comparator)(void *, void *))
{
    int result = comparator(node->data, new_node->data);

    if (result > 0)
    {
        if (node->left == NULL)
        {
            node->left = new_node;
        }
        else
        {
            treeset_insert(node->left, new_node, comparator);
        }
    }
    else if (result < 0)
    {
        if (node->right == NULL)
        {
            node->right = new_node;
        }
        else
        {
            treeset_insert(node->right, new_node, comparator);
        }
    }
}

static TreeNode *treeset_search(TreeNode *node, void *data, int (*comparator)(void *, void *))
{
    if (node == NULL)
    {
        return NULL;
    }

    int result = comparator(node->data, data);

    if (result > 0)
    {
        return treeset_search(node->left, data, comparator);
    }
    else if (result < 0)
    {
        return treeset_search(node->right, data, comparator);
    }
    else
    {
        return node;
    }
}

static void treeset_foreach0(TreeNode *node, void (*consumer)(void *))
{
    if (node == NULL)
    {
        return;
    }

    treeset_foreach0(node->left, consumer);
    consumer(node->data);
    treeset_foreach0(node->right, consumer);
}

static void treeset_clean0(TreeNode *node, void (*destroyer)(void *))
{
    if (node == NULL)
    {
        return;
    }

    treeset_clean0(node->left, destroyer);
    treeset_clean0(node->right, destroyer);

    destroyer(node->data);
    free(node);
}

static TreeNode *treeset_find_subsequent_node_parent(TreeNode *node)
{
    if (node->left != NULL && node->left->left != NULL)
    {
        return treeset_find_subsequent_node_parent(node->left);
    }
    else if (node->left != NULL && node->left->left == NULL)
    {
        return node;
    }
    else
    {
        return node;
    }
}

static TreeNode *treeset_find_subsequent_node(TreeNode *node)
{
    if (node->left != NULL)
    {
        return treeset_find_subsequent_node(node->left);
    }
    else
    {
        return node;
    }
}

static int treeset_remove0(TreeSet *treeSet, TreeNode *parent, TreeNode *node, void *data, void (*destroyer)(void *))
{
    if (node == NULL)
    {
        return 0;
    }

    int result = treeSet->comparator(node->data, data);

    if (result > 0)
    {
        return treeset_remove0(treeSet, node, node->left, data, destroyer);
    }
    else if (result < 0)
    {
        return treeset_remove0(treeSet, node, node->right, data, destroyer);
    }
    else
    {
        //#region 删除算法规则一：如果要删除的结点没有子结点，就直接删掉它
        if (node->left == NULL && node->right == NULL)
        {
            if (parent == NULL)
            {
                treeSet->root = NULL;
            }
            else
            {
                if (parent->left == node)
                {
                    parent->left = NULL;
                }
                else if (parent->right == node)
                {
                    parent->right = NULL;
                }
            }

            destroyer(node->data);
            free(node);

            return 1;
        }
        //#endregion

        //#region 删除算法规则二：如果要删除的结点有一个子结点，那删掉它之后，还要将子结点填到被删除结点的位置上

        if ((node->left != NULL && node->right == NULL) || (node->right != NULL && node->left == NULL))
        {
            if (parent == NULL)
            {
                treeSet->root = node->left;

                if (treeSet->root == NULL)
                {
                    treeSet->root = node->right;
                }
            }
            else
            {
                if (parent->left == node)
                {
                    parent->left = node->left;

                    if (parent->left == NULL)
                    {
                        parent->left = node->right;
                    }
                }
                else if (parent->right == node)
                {
                    parent->right = node->left;

                    if (parent->right == NULL)
                    {
                        parent->right = node->right;
                    }
                }
            }

            destroyer(node->data);
            free(node);

            return 1;
        }

        //#endregion

        //#region 删除算法规则三：如果要删除的结点有两个子结点，则将该结点替换成其后继结点

        TreeNode *subsequent_node = treeset_find_subsequent_node(node->right);

        //#region 删除算法规则四：如果后继结点带有右子结点，则在后继结点填补被删除结点以后，用此右子结点替代后继结点的父节点的左子结点

        if (subsequent_node->right != NULL)
        {
            TreeNode *subsequent_node_parent = treeset_find_subsequent_node_parent(node->right);

            subsequent_node_parent->left = subsequent_node->right;
        }

        //#endregion

        if (parent == NULL)
        {
            treeSet->root = subsequent_node;
        }
        else
        {
            if (parent->left == node)
            {
                parent->left = subsequent_node;
            }
            else if (parent->right == node)
            {
                parent->right = subsequent_node;
            }
        }

        destroyer(node->data);
        free(node);

        return 1;
        //#endregion
    }
}

void treeset_add(TreeSet *treeSet, void *data)
{
    treeSet->size++;

    TreeNode *newNode = malloc(sizeof(TreeNode));
    memset(newNode, 0, sizeof(TreeNode));
    newNode->data = data;

    if (treeSet->root == NULL)
    {
        treeSet->root = newNode;

        return;
    }

    treeset_insert(treeSet->root, newNode, treeSet->comparator);
}

void treeset_remove(TreeSet *treeSet, void *data, void (*destroyer)(void *))
{
    int result = treeset_remove0(treeSet, NULL, treeSet->root, data, destroyer);

    if (result)
    {
        treeSet->size--;
    }
}

int treeset_contains(TreeSet *treeSet, void *data)
{
    TreeNode *node = treeset_search(treeSet->root, data, treeSet->comparator);

    return node != NULL ? EXISTS : NOT_EXISTS;
}

void treeset_foreach(TreeSet *treeSet, void (*consumer)(void *))
{
    treeset_foreach0(treeSet->root, consumer);
}

void treeset_clean(TreeSet *treeSet, void (*destroyer)(void *))
{
    treeset_clean0(treeSet->root, destroyer);

    treeSet->root = NULL;
    treeSet->size = 0;
}