#include "FIFOHead.h"

#include <stdlib.h>
#include <stdio.h>

FHQueue* QFCreate() {
	FHQueue* q = (FHQueue*)calloc(1, sizeof(FHQueue));
	if (!q) return NULL;
	q->pHead = (FHQItem*)calloc(1, sizeof(FHQItem));
	// Jeœli nie uda³o siê zalokowaæ zwalniamy pamiêæ i zwracamy NULL
	if (!q->pHead) {
		free(q);
		return NULL;
	}
	// W chwili utworzenia pTail wskazuje na g³owê
	q->pHead->next = NULL;
	q->pTail = q->pHead;
}

int QFEmpty(FHQueue* q) {
	return !q->pHead->next;
}

void QFEnqueue(FHQueue* q, int x) {
	// Tworzymy nowy element jako nastêpuj¹cy po tailu
	q->pTail->next = (FHQItem*)calloc(1, sizeof(FHQItem));
	if (!q->pTail->next) {
		printf("Error: alloc\n");
		return;
	}
	//  Jeœli alokacja siê powiod³a, ten element staje siê naszym tailem, nastêpnie go uzupe³niamy
	q->pTail = q->pTail->next;
	//	q->pTail->next = NULL;
	q->pTail->nKey = x;
}

FHQItem* QFDequeue(FHQueue* q) {
	if (QFEmpty(q)) return NULL;
	FHQItem* res = q->pHead->next;
	QFDel(q);
	return res;
}

void QFClear(FHQueue* q) {
	// Zwalniamy pamiêæ, dopóki s¹ elementy w liœcie
	while (!QFEmpty(q)) {
		free(QFDequeue(q));
	}
}

void QFRemove(FHQueue** q) {
	QFClear(*q);
	free(*q);
	*q = NULL;
}

void QFDel(FHQueue* q) {
	if (QFEmpty(q)) return;
	q->pHead->next = q->pHead->next->next;
	if (QFEmpty(q))
		q->pTail = q->pHead;
}
