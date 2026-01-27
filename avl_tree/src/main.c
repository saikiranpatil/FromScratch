#include<stdio.h>
#include "avl_tree.h"
#include "print_util.h"

int main() {
    Tree* t = NULL;

    int values[] = {5, 15, 18, 19};
    for (int i = 0; i < 5; i++) t = insert(t, values[i]);

    printAsciiTree(t);
    
    return 0;
}