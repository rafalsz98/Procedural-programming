#include "FIFOArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// -- private -- //
// Usuniêcie pierwszego elementu (bez zwolnienia pamieci)
void QFDel(FAQueue* q) {

	// Ostatni element staje siê Nullem, zmniejszamy nTail i rozmiar
	q->elTable[q->nHead] = NULL;
	q->nHead = (q->nHead + 1) % q->max;
	q->currsize--;
}
// --         -- //

FAQueue* QFCreate(int nSize) {
	FAQueue* q = (FAQueue*)calloc(1, sizeof(FAQueue));
	if (!q) return NULL;
	q->currsize = 0;
	q->max = nSize;
	q->nHead = 0;
	q->nTail = 0;
	q->elTable = (QFIFOITEM**)calloc(nSize, sizeof(QFIFOITEM*));
	if (!q->elTable)
	{
		free(q);
		return NULL;
	}
	return q;
}

int QFEmpty(FAQueue* q) {
	return !q->currsize;
}

void QFEnqueue(FAQueue* q, QFIFOITEM* pInfo) {
	if (q->currsize >= q->max) {
		printf("No size\n");
		return;
	}

	q->elTable[q->nTail] = pInfo;
	q->currsize++;
	q->nTail = (q->nTail + 1) % q->max;

}

QFIFOITEM* QFDequeue(FAQueue* q) {
	if (q->currsize <= 0)
		return NULL;

	// Pierwszy element jest naszym wynikiem
	QFIFOITEM* res = q->elTable[q->nHead];

	// Usuwamy ten element z tablicy i zwracamy wynik
	QFDel(q);

	return res;
}

void QFClear(FAQueue* q) {
	// Zwalniamy pamiêæ dla ka¿dego elementu tablicy
	while (!QFEmpty(q)) {
		free(QFDequeue(q));
	}
}

void QFRemove(FAQueue** q) {
	QFClear(*q);
	free(*q);
	*q = NULL;
}