#pragma once
#include "global.h"

typedef struct {
	QPRIORINFO* pInfo;
	int nPrior;
} PQItem;

typedef struct {
	PQItem** queue;
	int PQSize; // Max size
	int PQurrSize;
} PQueue;

PQueue* PQInit(int size);
int PQisEmpty(PQueue*);
void PQEnqueue(PQueue*, QPRIORINFO*, int nPrior);
QPRIORINFO* PQDequeue(PQueue*);
void PQClearQueue(PQueue*);
void PQRelease(PQueue**);
void PQPrint(PQueue*);

void DecreaseKey(PQueue*, QPRIORINFO* pInfo, int nPrior);
void IncreaseKey(PQueue*, QPRIORINFO* pInfo, int nPrior);