#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "print_util.h"

Tree* createNode(int data) {
    Tree* node = malloc(sizeof(Tree));

    assert(node!=NULL);

    node->left=NULL;
    node->right=NULL;
    node->data=data;
    node->height=0;

    return node;
}

int max(int a, int b) {
    return a>b ? a : b;
}

int getHeight(Tree* t) {
    return t ? t->height : 0;
}

Tree* insert(Tree* t, int data) {
    if(!t) return createNode(data);

    if(data>t->data) t->right = insert(t->right, data);
    else if(data<t->data) t->left = insert(t->left, data);
    else return t;

    t->height=1+max(getHeight(t->left), getHeight(t->right));

    int factor = getHeight(t->left) - getHeight(t->right);

    // Left Right Rotation
    if(factor>1 && data>t->data) {
        Tree* 
    }

    return t;
}