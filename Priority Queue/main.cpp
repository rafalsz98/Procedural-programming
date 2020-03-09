#include <iostream>
#include "PriorityQueue.h"

#define MAX 4
using namespace std;

QPRIORINFO* CreateInfo(int nKey);


int main()
{
	PQueue* q = PQInit(MAX);

	// Wype³nienie kolejki liczbami
	for (int i = 0; i < MAX; i++) {
		PQEnqueue(q, CreateInfo(i + 1), i);
	}

	PQPrint(q);
	cout << endl << endl;

	DecreaseKey(q, q->queue[2]->pInfo, 0);
	IncreaseKey(q, q->queue[1]->pInfo, 4);


	PQPrint(q);

	cout << endl;



	for (int i = 0; i < MAX; i++) {
		QPRIORINFO* it = PQDequeue(q);
		cout << it->nKey << " ";
		free(it);
	}

	PQRelease(&q);


	return 0;
}

QPRIORINFO* CreateInfo(int nKey) {
	QPRIORINFO* info = (QPRIORINFO*)calloc(1, sizeof(QPRIORINFO));
	if (!info) return NULL;
	info->nKey = nKey;
	return info;

}
