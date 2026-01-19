#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <stddef.h>

typedef struct Table Table;
Table* init_table();
void erase_table(Table* t);
void insert(Table** tp, int num);
bool search(Table* t, int num);
void remove_key(Table* t, int num);

#endif