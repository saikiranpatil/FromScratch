/**
 * OPEN HASHING
 * simple open-hashing implementation of unordered_set
 * using simple hashing and linked-list 
 * for collusion handling
 */

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#define INITIAL_TABLE_SIZE 256

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Table {
    size_t capacity;
    Node* buckets[];
} Table;

Table* create_table() {
    Table *t=(Table*) malloc(sizeof(Table) + INITIAL_TABLE_SIZE * sizeof(Node*));
    t->capacity = INITIAL_TABLE_SIZE;
    for(int i=0;i<INITIAL_TABLE_SIZE;i++) t->buckets[i]=NULL;
    return t;
}

int hash(int num) {
    return (num % INITIAL_TABLE_SIZE + INITIAL_TABLE_SIZE) % INITIAL_TABLE_SIZE;
}

void insert(Table* t, int data) {
    int hash_value=hash(data);

    Node* curr = t->buckets[hash_value];

    while(curr) {
        if(curr->value == data) return; // already exists
        curr=curr->next;
    }

    Node* newNode=malloc(sizeof(Node));
    newNode->value=data;
    newNode->next=t->buckets[hash_value];
    t->buckets[hash_value]=newNode;
}

int count(Table* t, int num) {
    int hash_value = hash(num);

    Node* curr=t->buckets[hash_value];
    while(curr) {
        if(curr->value==num) return 1;
        curr=curr->next;
    }
    
    return 0;
}

void clear_table(Table* t) {
    free(t);
}

int main() {
    Table* t = create_table();

    insert(t, 0);
    insert(t, 0);
    insert(t, 6);
    insert(t, 9);
    insert(t, 10);
    insert(t, INT_MAX);

    printf("9 found: %d\n", count(t, 9));
    printf("2 found: %d\n", count(t, 2));
    printf("0 found: %d\n", count(t, 0));
    printf("INT_MAX found: %d\n", count(t, INT_MAX));
}