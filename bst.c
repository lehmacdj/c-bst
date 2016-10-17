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
    if (bst == NULL)
        return;
    destroy_bst(bst->left);
    destroy_bst(bst->right);
    bst = NULL;
}

int bst_search(struct BST* bst, int k) {
    struct BST* b = bst;
    while (b != NULL) {
        if (k < bst->key)
            b = bst->left;
        else if (bst->key == k)
            return bst->value;
        else
            b = bst->right;
    }
    return 0;
}

// consider implementing iteratively for better performance but worse
// readability
void bst_insert(struct BST* bst, int k, int v) {
    if (bst == NULL) {
        bst = create_bst(k, v);
        return;
    }

    if (k < bst->key)
        bst_insert(bst->left, k, v);
    else if (k == bst->key)
        bst->value = v;
    else
        bst_insert(bst->right, k, v);
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
