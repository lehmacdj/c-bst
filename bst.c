#include "bst.h"
#include <stdlib.h>

struct BST* create_bst(int k, int v) {
    struct BST* bst = malloc(sizeof(struct BST*));
    bst->key = k;
    bst->value = v;
    bst->left = NULL;
    bst->right = NULL;
    return bst;
}

void destroy_bst(struct BST* bst) {
    destroy_bst(bst->left);
    destroy_bst(bst->right);
    free(bst);
    bst = NULL;
}

/**
 * Returns the subtree of [bst] with root [k] if [k] is in the tree otherwise
 * returns NULL.
 */
struct BST* tree_with_root_key(struct BST* bst, int k) {
    struct BST* b = bst;
    while (b->left != NULL && b->right != NULL && k != b->key) {
        if (k < bst->key)
            b = bst->left;
        else if (k > bst->key)
            b = bst->right;
    }

    if (k == b->key)
        return bst;
    else
        return NULL;
}

int* bst_search(struct BST* bst, int k) {
    struct BST* b = tree_with_root_key(bst, k);

    if (b != NULL)
        return &b->value;
    else
        return NULL;
}

// consider implementing iteratively for better performance but worse
// readability
void bst_insert(struct BST* bst, int k, int v) {
    struct BST* b = tree_with_root_key(bst, k);

    if (b == NULL)
        return;
}

void bst_delete(struct BST* bst, int k) {
    if (bst == NULL)
        return;

    if (k < bst->key) {
        bst_delete(bst->left, k);
    } else if (k == bst->key) {
        // implement this case
    } else {
        bst_delete(bst->right, k);
    }
}
