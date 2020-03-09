#define FIFOARRAY
//#define FIFOHEAD
//#define FIFOHEADLESS



#include <iostream>
#include <stdlib.h> 
#include "global.h"

#ifdef FIFOHEAD
#include "FIFOHead.h"
#endif // 

#ifdef FIFOARRAY
#include "FIFOArray.h"
#endif // FIFOARRAY

#ifdef FIFOHEADLESS
#include "FIFOHeadless.h"
#endif // FIFOHEADLESS


//#include <iostream>


using namespace std;
#define MAX 4

QFIFOITEM* CreateItem(int nKey);

int main() {

#ifdef FIFOARRAY
	FAQueue* q = QFCreate(MAX);


	for (int i = 0; i < MAX; i++) {
		QFEnqueue(q, CreateItem(i));
	}
	free(QFDequeue(q));
	QFEnqueue(q, CreateItem(10));

	while (!QFEmpty(q)) {
		QFIFOITEM* it = QFDequeue(q);
		cout << it->nKey << " ";
		free(it);
	}

	cout << endl;
	QFRemove(&q);
#endif

#ifdef FIFOHEAD
	FHQueue* q = QFCreate();
	QFEnqueue(q, 2);
	QFEnqueue(q, 3);
	QFEnqueue(q, 4);
	free(QFDequeue(q));
	QFEnqueue(q, 5);
	while (!QFEmpty(q)) {
		FHQItem* it = QFDequeue(q);
		cout << it->nKey << " ";
		free(it);
	}
	QFRemove(&q);
#endif // FIFOHEAD

#ifdef FIFOHEADLESS
	FHLQueue* q = QFCreate();
	QFEnqueue(q, 1);
	QFEnqueue(q, 2);
	QFEnqueue(q, 3);
	free(QFDequeue(q));
	QFEnqueue(q, 4);
	while (!QFEmpty(q)) {
		FHLQItem* it = QFDequeue(q);
		cout << it->nKey << " ";
		free(it);
	}
	QFRemove(&q);
#endif // FIFOHEADLESS


	return 0;
}

QFIFOITEM* CreateItem(int nKey) {
	QFIFOITEM* item = (QFIFOITEM*)calloc(1, sizeof(QFIFOITEM));
	if (!item) return NULL;
	item->nKey = nKey;
	return item;
}