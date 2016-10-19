#pragma once

/**
 * Represents a BST with ints as keys and values. Keys in [left] are < [key]
 * and keys in [right] are > [key].
 */
struct BST {
    int key;
    int value;
    struct BST* left;
    struct BST* right;
};

/**
 * Return a BST with initial key [k] and value [v].
 */
struct BST* create_bst(int k, int v);

/**
 * Destroy [bst].
 * Precondition bst != NULL.
 */
void destroy_bst(struct BST* bst);

/**
 * Return the value associated with [k] in [bst]. If [k] is not in [bst]
 * behavior is undefined.
 * Precondition bst != NULL.
 */
int bst_search(struct BST* bst, int k);

/**
 * Insert [(k, v)] into [bst]. If [k] is already in [bst] behavior is undefined.
 * Precondition bst != NULL.
 */
void bst_insert(struct BST* bst, int k, int v);

/**
 * Delete the key and value associated with [k] from [bst]. If [k] is not in
 * [bst] do nothing.
 * Precondition bst != NULL.
 */
void bst_delete(struct BST* bst, int k);
