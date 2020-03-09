#include "FIFOHead.h"

#include <stdlib.h>
#include <stdio.h>

FHQueue* QFCreate() {
	FHQueue* q = (FHQueue*)calloc(1, sizeof(FHQueue));
	if (!q) return NULL;
	q->pHead = (FHQItem*)calloc(1, sizeof(FHQItem));
	// Je�li nie uda�o si� zalokowa� zwalniamy pami�� i zwracamy NULL
	if (!q->pHead) {
		free(q);
		return NULL;
	}
	// W chwili utworzenia pTail wskazuje na g�ow�
	q->pHead->next = NULL;
	q->pTail = q->pHead;
}

int QFEmpty(FHQueue* q) {
	return !q->pHead->next;
}

void QFEnqueue(FHQueue* q, int x) {
	// Tworzymy nowy element jako nast�puj�cy po tailu
	q->pTail->next = (FHQItem*)calloc(1, sizeof(FHQItem));
	if (!q->pTail->next) {
		printf("Error: alloc\n");
		return;
	}
	//  Je�li alokacja si� powiod�a, ten element staje si� naszym tailem, nast�pnie go uzupe�niamy
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
	// Zwalniamy pami��, dop�ki s� elementy w li�cie
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
