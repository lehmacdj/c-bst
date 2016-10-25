#pragma once

/**
 * The value of the thing in the tree.
 */
typedef int V;

/**
 * A function poVer type for something that consumes values of the trees and
 * returns nothing.
 */
typedef void (*Consumer)(V);

/**
 * Represents a BST with ints as keys and values. Keys in [left] are < [key]
 * and keys in [right] are > [key].
 */
struct BST {
    int key;
    V value;
    struct BST* left;
    struct BST* right;
    struct BST* parent;
};

/**
 * Return a BST with initial key [k] and value [v].
 */
struct BST* create_bst(int k, V v);

/**
 * Destroy [bst].
 * Precondition bst != NULL.
 */
void destroy_bst(struct BST* bst);

/**
 * Return a pointer to the value associated with [k] in [bst]. If [k] is not in
 * the bst return NULL.
 * Precondition bst != NULL.
 */
int* bst_search(struct BST* bst, int k);

/**
 * Insert [(k, v)] into [bst]. If [k] is already in [bst] change the previous
 * value instead of inserting.
 * Precondition bst != NULL.
 */
void bst_insert(struct BST* bst, int k, V v);

/**
 * Delete the key and value associated with [k] from [bst]. If [k] is not in
 * [bst] do nothing.
 * Precondition bst != NULL.
 */
void bst_delete(struct BST* bst, int k);


/**
 * Does an in order traversal of [bst] calling [c] on each node.
 */
void traverse(struct BST* bst, Consumer c);
