#pragma once
#include <stdio.h>

typedef struct tagIntList {
	int key;
	tagIntList* next;
} IntList;

IntList* CreateList();
void Insert(IntList* head, int x);
void FreeList(IntList* head);
int IsEmpty(IntList* head);
void PrintList(IntList* head, FILE* fout);
int LastListItem(IntList* head);