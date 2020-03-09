#include "PriorityQueue.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


void UpdateUp(PQueue*, int L, int R);
void UpdateDown(PQueue*, int L, int R);

PQueue* PQInit(int size) {
	PQueue* q = (PQueue*)calloc(1, sizeof(PQueue));
	if (!q) return NULL;
	q->PQSize = size;

	q->queue = (PQItem**)calloc(size, sizeof(PQItem*));
	if (!q->queue) {
		free(q);
		return NULL;
	}
	return q;
}

int PQisEmpty(PQueue* q) {
	return !q->PQurrSize;
}

void PQEnqueue(PQueue* q, QPRIORINFO* info, int nPrior) {
	if (q->PQurrSize >= q->PQSize)
	{
		printf("No more space in queue!\n");
		return;
	}

	PQItem* item = (PQItem*)calloc(1, sizeof(PQItem));
	if (!item)
	{
		printf("Err: Alloc\n");
		return;
	}
	item->pInfo = info;
	item->nPrior = nPrior;


	q->queue[q->PQurrSize] = item;
	q->PQurrSize++;
	UpdateUp(q, 0, q->PQurrSize - 1);

}

QPRIORINFO* PQDequeue(PQueue* q) {
	if (!q->PQurrSize) return NULL;

	QPRIORINFO* res = q->queue[0]->pInfo;
	free(q->queue[0]);
	q->queue[0] = NULL;

	int i = q->PQurrSize - 1;

	q->queue[0] = q->queue[i];
	q->queue[i] = NULL;
	UpdateDown(q, 0, i - 1);

	q->PQurrSize--;

	return res;
}

void PQClearQueue(PQueue* q) {
	while (!PQisEmpty(q)) {
		free(PQDequeue(q));
	}
}

void PQRelease(PQueue** q) {
	PQClearQueue(*q);
	free(*q);
	*q = NULL;
}

void PQPrint(PQueue* q) {
	int level = 0;
	for (int i = 0; i < q->PQurrSize; i++) {
		cout << "P:" << q->queue[i]->nPrior << "|K:" << q->queue[i]->pInfo->nKey << "  ";
		if (i == level) {
			cout << endl;
			level = level * 2 + 2;
		}
	}

}


void DecreaseKey(PQueue* q, QPRIORINFO* pInfo, int nPrior) {
	int i = 0;
	while (i < q->PQurrSize && q->queue[i]->pInfo != pInfo)
		i++;

	if (i == q->PQurrSize) return;
	if (nPrior >= q->queue[i]->nPrior) return;

	q->queue[i]->nPrior = nPrior;
	UpdateDown(q, i, q->PQurrSize - 1);


}

void IncreaseKey(PQueue* q, QPRIORINFO* pInfo, int nPrior) {
	int i = 0;
	while (i < q->PQurrSize && q->queue[i]->pInfo != pInfo)
		i++;

	if (i == q->PQurrSize) return;
	if (nPrior <= q->queue[i]->nPrior) return;

	q->queue[i]->nPrior = nPrior;
	UpdateUp(q, 0, i);

}


void UpdateDown(PQueue* q, int L, int R) {
	if (L == R) return;
	int i = L;
	int j = 2 * i + 1;
	PQItem* x = q->queue[i];

	while (j <= R) {
		if (j < R) {
			if (q->queue[j]->nPrior < q->queue[j + 1]->nPrior)
				j++;
		}
		if (x->nPrior > q->queue[j]->nPrior)
			break;
		q->queue[i] = q->queue[j];
		i = j;
		j = 2 * j + 1;
	}
	q->queue[i] = x;
}

void UpdateUp(PQueue* q, int L, int R) {
	int i = R;

	while (i != 0 && q->queue[(i - 1) / 2]->nPrior < q->queue[i]->nPrior) {
		PQItem* temp = q->queue[i];
		q->queue[i] = q->queue[(i - 1) / 2];
		q->queue[(i - 1) / 2] = temp;
		i = (i - 1) / 2;
	}
}