#include "IntList.h"
#include <stdlib.h>
#include <stdio.h>

IntList* CreateList()
{
	IntList* list = (IntList*)calloc(1, sizeof(IntList));
	return list;
}

void Insert(IntList* head, int x)
{
	IntList* item = (IntList*)calloc(1, sizeof(IntList));
	if (!item)
	{
		printf("Err: Alloc\n");
		return;
	}
	item->key = x;
	IntList* it = head;

	while (it->next)
		it = it->next;
	it->next = item;
}

void FreeList(IntList* head)
{
	IntList* it = head->next;
	while (it)
	{
		IntList* del = it;
		it = it->next;
		free(del);
	}
	free(head);
}

int IsEmpty(IntList* head)
{
	return !head->next;
}

void PrintList(IntList* head, FILE* fout)
{
	IntList* it = head;
	while (it->next)
	{
		fprintf(fout, "%d, ", it->next->key);
		it = it->next;
	}
}

int LastListItem(IntList* head)
{
	IntList* it = head;
	while (it->next)
		it = it->next;
	return it->key;
}
