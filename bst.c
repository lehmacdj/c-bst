#include "bst.h"
#include <stdlib.h>

struct BST* create_bst(int k, V v) {
    struct BST* bst = malloc(sizeof(struct BST*));
    bst->key = k;
    bst->value = v;
    bst->left = NULL;
    bst->right = NULL;
    bst->parent = NULL;
    return bst;
}

void destroy_bst(struct BST* bst) {
    if (bst == NULL)
        return;

    destroy_bst(bst->left);
    destroy_bst(bst->right);
    free(bst);
    bst = NULL;
}

/**
 * Returns the subtree of [bst] closest to [k].
 */
struct BST* tree_containing_key(struct BST* bst, int k) {
    struct BST* b = bst;
    while (b->left != NULL && b->right != NULL && k != b->key) {
        if (k < bst->key)
            b = bst->left;
        else if (k > bst->key)
            b = bst->right;
    }

    return bst;
}

V* bst_search(struct BST* bst, int k) {
    struct BST* b = tree_containing_key(bst, k);
    return b->key == k ? &b->value : NULL;
}

void bst_insert(struct BST* bst, int k, V v) {
    struct BST* b = tree_containing_key(bst, k);

    if (b->key < k) {
        b->left = create_bst(k, v);
        b->left->parent = b;
    } else if (b->key == k) {
        b->value = v;
    } else {
        b->right = create_bst(k, v);
        b->right->parent = b;
    }
}

/**
 * Find the minimum key in the tree.
 */
struct BST* find_min(struct BST* bst) {
    return NULL;
}

/**
 * Replace [bst] with [node]. [node] should be an orphaned node (e.g. has no
 * pointers to it within the tree).
 */
void replace_node(struct BST* bst, struct BST* node) {
    struct BST* parent = bst->parent;
    free(bst);

    if (parent->left == node)
        parent->left = node;
    else if (parent->right == node)
        parent->right = node;

    if (node != NULL)
        node->parent = parent;
}

void bst_delete(struct BST* bst, int k) {
    struct BST* b = tree_containing_key(bst, k);

    if (b->key != k)
        return;

    if (b->left != NULL && b->right != NULL) {
        struct BST* mid = find_min(b->right);
        mid->parent->left = NULL;
        mid->left = b->left;
        mid->right = b->right;
        replace_node(b, mid);
    } else if (b->left != NULL) {
        replace_node(b, b->right);
    } else if (b->right != NULL) {
        replace_node(b, b->left);
    } else {
        replace_node(b, NULL);
    }
}

void bst_traverse_value(struct BST* bst, VConsumer c) {
    if (bst == NULL)
        return;

    bst_traverse_value(bst->left, c);
    (*c)(bst->value);
    bst_traverse_value(bst->right, c);
}

void bst_traverse_node(struct BST* bst, NConsumer c) {
    if (bst == NULL)
        return;

    bst_traverse_node(bst->left, c);
    (*c)(bst->key, bst->value);
    bst_traverse_node(bst->right, c);
}
