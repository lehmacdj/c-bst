#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

void printbst(struct BST* bst) {
    printf("[%p](%d, %d)[%p, %p] at %p\n",
           bst->parent,
           bst->key,
           bst->value,
           bst->left,
           bst->right,
           bst);
}

struct BST* create_bst(int k, V v) {
    struct BST* bst = malloc(2 * sizeof(int) + 3 * sizeof(void*));
    if (bst == NULL) {
        printf("Wasn't able to allocate memory!");
        return NULL;
    }

    bst->key = k;
    bst->value = v;
    bst->left = NULL;
    bst->right = NULL;
    bst->parent = NULL;
    return bst;
}

void destroy_bst(struct BST* bst) {
    printf("destroy bst: %p\n", bst);
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
    while ((k < b->key && b->left != NULL) ||
            (k > b->key && b->right != NULL)) {
        if (k < bst->key)
            b = bst->left;
        else if (k > bst->key)
            b = bst->right;
    }

    return b;
}

V* bst_search(struct BST* bst, int k) {
    struct BST* b = tree_containing_key(bst, k);
    return b->key == k ? &b->value : NULL;
}

void bst_insert(struct BST* bst, int k, V v) {
    struct BST* b = tree_containing_key(bst, k);

    if (k < b->key) {
        b->left = create_bst(k, v);
        b->left->parent = b;
    } else if (k == b->key) {
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

void bst_traverse_bst(struct BST* bst, BConsumer c) {
    if (bst == NULL)
        return;

    bst_traverse_bst(bst->left, c);
    (*c)(bst);
    bst_traverse_bst(bst->right, c);
}
