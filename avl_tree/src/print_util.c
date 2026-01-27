#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl_tree.h"

typedef struct NodePos {
    struct Tree* node;
    int x;
    int y;
} NodePos;

#define MAX_HEIGHT 250
#define MAX_WIDTH 250

typedef struct LevelPos {
    char line[MAX_WIDTH];
} LevelPos;

void clearLevels(LevelPos levels[], int h) {
    for (int i = 0; i < h; i++)
        memset(levels[i].line, ' ', MAX_WIDTH - 1);
}

int computePositions(struct Tree* root, int x, int y, NodePos positions[], int* idx) {
    if (!root) return x;

    x = computePositions(root->left, x, y + 2, positions, idx);

    positions[*idx].node = root;
    positions[*idx].x = x;
    positions[*idx].y = y;
    (*idx)++;

    x += (root->data < 10) ? 2 : (int)log10(root->data) + 3; 

    x = computePositions(root->right, x, y + 2, positions, idx);

    return x;
}

void printAsciiTree(struct Tree* root) {
    if (!root) return;

    NodePos positions[1024];
    int idx = 0;
    int h = 0;

    computePositions(root, 0, 0, positions, &idx);

    LevelPos levels[MAX_HEIGHT];
    clearLevels(levels, MAX_HEIGHT);

    // Place nodes into lines
    for (int i = 0; i < idx; i++) {
        int x = positions[i].x;
        int y = positions[i].y;
        char buf[16];
        sprintf(buf, "%d", positions[i].node->data);
        strncpy(&levels[y].line[x], buf, strlen(buf));
        if (y + 1 < MAX_HEIGHT) {
            // Add branches
            if (positions[i].node->left)
                levels[y + 1].line[x - 1] = '/';
            if (positions[i].node->right)
                levels[y + 1].line[x + 1] = '\\';
        }
        if (y > h) h = y;
    }

    // Print all levels
    for (int i = 0; i <= h + 1; i++) {
        levels[i].line[MAX_WIDTH - 1] = '\0';
        printf("%s\n", levels[i].line);
    }
}
