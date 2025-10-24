#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <stdio.h>

struct node{    // node with value and link to next and prev node
    int data;
    node *next;
    node *prev;
};

struct List{    // list which contain info about link head and tail, and size
    node *head;
    node *tail;
    size_t size;
};

void listInit(List *l);
void listPushBack(List *l, int value);

void listPrintForward(List *l);
void listPrintBackward(List *l);

void listPushFront(List *l, int value);

int listPopFront(List *l);
int listPopBack(List *l);

void listDestroy(List *l);

#endif //LIST_H
