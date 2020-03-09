#pragma once
#include "global.h"

typedef struct {
	QFIFOITEM** elTable;
	int nHead;
	int nTail;
	int currsize;
	int max;
} FAQueue;

FAQueue* QFCreate(int nSize); //NULL fail
int QFEmpty(FAQueue* q);
void QFEnqueue(FAQueue* q, QFIFOITEM* pInfo);
QFIFOITEM* QFDequeue(FAQueue* q); //bez zwalniania pamiêci
void QFClear(FAQueue* q); //frees memory for queue items
void QFRemove(FAQueue** q);