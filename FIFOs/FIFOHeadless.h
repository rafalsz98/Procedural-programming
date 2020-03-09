#pragma once

typedef struct tagFHLQItem {
	int nKey;
	tagFHLQItem* next;
} FHLQItem;

typedef struct {
	FHLQItem* pHead;
	FHLQItem* pTail;
} FHLQueue;

FHLQueue* QFCreate(); //NULL fail
int QFEmpty(FHLQueue* q);
void QFEnqueue(FHLQueue* q, int x); //new item at the end
FHLQItem* QFDequeue(FHLQueue* q); //bez zwalniania pamiêci
void QFClear(FHLQueue* q); //frees memory for queue items
void QFRemove(FHLQueue** q); // clears the queue (=QFClear()) and removes
void QFDel(FHLQueue* q); //removes only first item


