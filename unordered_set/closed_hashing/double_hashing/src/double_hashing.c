#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.h"

#define LOAD_FACTOR 0.75
#define INITIAL_TABLE_SIZE 256

typedef enum STATE {
    EMPTY,
    PRESENT,
    DELETED
} STATE;

typedef struct Table {
    size_t size;
    size_t capacity;
    int* keys;
    STATE* states;
} Table;

Table* create_table(size_t capacity) {
    assert(capacity>1);
    
    Table* t=malloc(sizeof(Table));
    assert(t!=NULL);
    
    t->size=0;
    t->capacity=capacity;
    t->keys=calloc(capacity, sizeof *t->keys);
    t->states=calloc(capacity, sizeof *t->states);
    
    assert(t->keys!=NULL);
    assert(t->states!=NULL);
    
    return t;
}

Table* init_table() {
    return create_table(INITIAL_TABLE_SIZE);
}

void erase_table(Table* t) {
    free(t->keys);
    free(t->states);
    free(t);
}

void insert(Table** tp, int num);

void rehash(Table** tp) {
    Table* t = *tp;
    size_t capacity = t->capacity;
    Table* new_table = create_table(capacity*2);

    for(size_t idx=0;idx<t->capacity;idx++) {
        if(t->states[idx]!=PRESENT) continue;

        insert(&new_table, t->keys[idx]);
    }

    erase_table(t);
    *tp=new_table;
}

void insert(Table** tp, int num) {
    Table* t=*tp;

    if(((float) t->size) / t->capacity >= LOAD_FACTOR) {
        rehash(tp);
        t=*tp;
    }

    size_t delete_idx = (size_t)-1;
    size_t hash_value;
    bool found_duplicate = false;

    for(size_t idx=0;idx<t->capacity;idx++) {
        hash_value = hash(t->capacity, num, idx);
        STATE curr_state = t->states[hash_value];

        if(PRESENT==curr_state) {
            if(num==t->keys[hash_value]) {
                found_duplicate = true;
                break;
            }
        } else if(DELETED==curr_state) {
            if(delete_idx == (size_t) -1) delete_idx = hash_value;
        } else {
            break;
        }
    }

    if(found_duplicate) return;

    if(delete_idx != (size_t) -1) hash_value = delete_idx;
    
    t->size++;
    t->keys[hash_value]=num;
    t->states[hash_value]=PRESENT;
}

bool search(Table* t, int num) {
    size_t hash_value;
    for(size_t idx=0;idx<t->capacity;idx++) {
        hash_value = hash(t->capacity, num, idx);

        if(PRESENT==t->states[hash_value] && num==t->keys[hash_value]) {
            return true;
        }
        
        if(EMPTY==t->states[hash_value]) {
            return false;
        }
    }
    return false;
}

void remove_key(Table* t, int num) {
    size_t hash_value;
    for(size_t idx=0;idx<t->capacity;idx++) {
        hash_value = hash(t->capacity, num, idx);

        if(EMPTY==t->states[hash_value]) {
            return;
        }

        if(PRESENT==t->states[hash_value] && num==t->keys[hash_value]) {
            t->states[hash_value]=DELETED;
            t->size--;

            return;
        }
    }
}