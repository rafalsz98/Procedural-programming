#include "FIFOHeadless.h"

#include <stdlib.h>
#include <stdio.h>

FHLQueue* QFCreate() {
	FHLQueue* q = (FHLQueue*)calloc(1, sizeof(FHLQueue));
	if (!q)
		return NULL;
	//q->pHead = NULL;
	//q->pTail = NULL;
}

int QFEmpty(FHLQueue* q) {
	return !q->pHead;
}

void QFEnqueue(FHLQueue* q, int x) {
	// Tworzymy nowy element i go uzupe³niamy
	FHLQItem* item = (FHLQItem*)calloc(1, sizeof(FHLQItem));
	if (!item) {
		printf("Error: alloc\n");
		return;
	}
	item->next = NULL;
	item->nKey = x;

	// Rozbijamy na dwa warunki:
	// - Jeœli istnieje ju¿ pierwszy element, to wstawiamy utworzony element za tailem
	// - Jeœli nie, utworzony element staje siê naszym headem
	if (q->pHead) {
		q->pTail->next = item;
	}
	else {
		q->pHead = item;
	}
	q->pTail = item;
}

FHLQItem* QFDequeue(FHLQueue* q) {
	if (QFEmpty(q)) return NULL;
	FHLQItem* res = q->pHead;
	QFDel(q);
	return res;
}

void QFClear(FHLQueue* q) {
	while (!QFEmpty(q)) {
		free(QFDequeue(q));
	}
}

void QFRemove(FHLQueue** q) {
	QFClear(*q);
	free(*q);
	*q = NULL;
}

void QFDel(FHLQueue* q) {
	if (QFEmpty(q)) return;
	q->pHead = q->pHead->next;
	if (QFEmpty(q))
		q->pTail = NULL;
}