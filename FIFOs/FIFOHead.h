#pragma once

typedef struct tagFHQItem{
	int nKey;
	tagFHQItem* next;
}FHQItem;

typedef struct {
	FHQItem* pHead;
	FHQItem* pTail;
} FHQueue;

FHQueue* QFCreate(); //NULL fail
int QFEmpty(FHQueue* q);
void QFEnqueue(FHQueue* q, int x); //new item at the end
FHQItem* QFDequeue(FHQueue* q);
void QFClear(FHQueue* q); //frees memory for queue items
void QFRemove(FHQueue** q); // clears the queue (=QFClear()) and removes
void QFDel(FHQueue* q); //removes only first item
