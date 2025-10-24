#include "List.h"
#include <iostream>
#include <stdio.h>
#include <stdio.h>

void listInit(List *l){
    l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}
void listPushBack(List *l, int value){
    node* newnode = (node*)malloc(sizeof(node));
    if(!newnode) EXIT_FAILURE;
	newnode->data = value;
	newnode->next = NULL;
	newnode->prev = l->tail;
	if (l->tail) {
		l->tail->next = newnode;    //push link to new node to the last elem
	}
	else {
		l->head = newnode;          //or its a head
	}
	l->tail = newnode;
	l->size++;
}

void listPrintForward(List *l){
    printf("FWD (size=%zu): [", l->size);
	node* current = l->head;
	while (current) {
		printf("%d", current->data);
		if (current->next) {
			printf(" ");
		}
		current = current->next;
	}
	printf("]\n");
}

void listPrintBackward(List *l){
    printf("BWD (size=%zu): [", l->size);
	node* current = l->tail;
	while (current) {
		printf("%d", current->data);
		if (current->prev) {
			printf(" ");
		}
		current = current->prev;
	}
	printf("]\n");
}
void listPushFront(List *l, int value){
    node* newnode = (node*)malloc(sizeof(node));
    if(!newnode) EXIT_FAILURE;
	newnode->data = value;
	newnode->prev = NULL;
	newnode->next = l->head;
	if (l->head) {
		l->head->prev = newnode;    //push a link to new elem to the first elem(head)
	}
	else {
		l->tail = newnode;          // or its the only one elem
	}
	l->head = newnode;
	l->size++;
}

int listPopFront(List *l){
    if (l->head == NULL) {
		return -1; // List is empty
	}
	node* temp = l->head;
	int value = temp->data;
	l->head = l->head->next;
	if (l->head) {
		l->head->prev = NULL;
	}
	else {
		l->tail = NULL; // list is now empty
	}
	free(temp);
	l->size--;
	return value;
}

int listPopBack(List *l){
    if (l->tail == NULL) {
		return -1; // List is empty
	}
	node* temp = l->tail;
	int value = temp->data;
	l->tail = l->tail->prev;
	if (l->tail) {
		l->tail->next = NULL;
	}
	else {
		l->head = NULL; // list is now empty
	}
	free(temp);
	l->size--;
	return value;
}


void listDestroy(List *l){
	node* current = l->head;
	while (current) {
		node* next = current->next;
		free(current);
		current = next;
	}
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

