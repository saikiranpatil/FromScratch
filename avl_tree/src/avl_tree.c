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

Tree* leftRotation(Tree* x) {
    Tree* y = x->right;
    Tree* t2 = y->left;

    x->right=t2;
    y->left=x;

    return y;
}

Tree* rightRotation(Tree* y) {
    Tree* x = y->left;
    Tree* t2 = x->right;

    y->left = t2;
    x->right = y;

    return x;
}

Tree* insert(Tree* t, int data) {
    if(!t) return createNode(data);

    if(data>t->data) t->right = insert(t->right, data);
    else if(data<t->data) t->left = insert(t->left, data);
    else return t;

    t->height=1+max(getHeight(t->left), getHeight(t->right));

    int balanceFactor = getHeight(t->left) - getHeight(t->right);

    if(balanceFactor>1 && data>t->left->data) {
        // Left Right Rotation
        t->left = rightRotation(t->left);
        t = leftRotation(t);
    } else if(balanceFactor<-1 && data<t->right->data) {
        // Right Left Rotation
        t->right = rightRotation(t->right);
        t = leftRotation(t);
    } else if(balanceFactor>1 && data<t->left->data) {
        // Left Left Rotation
        t = leftRotation(t);
    } else if(balanceFactor<-1 && data>t->right->data) {
        // Right Right Rotation
        t = rightRotation(t);
    }

    return t;
}