#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct Tree {
    struct Tree *left;
    struct Tree *right;
    int height;
    int data;
} Tree;

Tree* insert(Tree* t, int data);

#endif
