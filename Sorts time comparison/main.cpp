#include <iostream>
#include <time.h>
#include "Sorts.h"
#include "Tab.h"

#define DEBUG

using namespace std;

typedef void (*pF)(int*, int);

// Funkcje pomocnicze, aby wskaźniki na funkcje działały poprawnie
void TQuickSort(int* tab, int nSize);
void TMergeSort1(int* tab, int nSize);
void TMergeSort2(int* tab, int nSize);

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: sorts <size of the array>\n");
		return -1;
	}
	int n = atoi(argv[1]);

	const char* sorts[] = {
		"SelectionSort",
		"InsertionSort",
		"HalfInsertionSort",
		"BubbleSort",
		"MixedBubbleSort",
		"QuickSort",
		"HeapSort",
		"MergeSort1",
		"MergeSort2",
	};

	pF ft[] = {
		SelectionSort,
		InsertionSort,
		HalfInsertionSort,
		BubbleSort,
		MixedBubbleSort,
		TQuickSort,
		HeapSort,
		TMergeSort1,
		TMergeSort2,
	};

	int sortCount = sizeof(ft) / sizeof(void*);

	int* firstTab = createTab(n);
	if (!firstTab) {
		printf("Error while allocating memory!\n");
		return -1;
	}

	randInit(firstTab, n);

	int* cTab = createTab(n);
	copyTab(cTab, firstTab, n);
	if (!cTab) {
		printf("Error while allocating memory!\n");
		return -1;
	}

	double clockStart = 0;
	double clockEnd = 0;

	for (int i = 0; i < sortCount; i++) {

#ifdef DEBUG
		for (int j = 0; j < n; j++) cout << cTab[j] << " ";
		cout << endl;
#endif // DEBUG

		clockStart = clock();
		ft[i](cTab, n);
		clockEnd = clock();

#ifdef DEBUG
		for (int j = 0; j < n; j++) cout << cTab[j] << " ";
		cout << endl;
#endif // DEBUG

		printf("%s: %.6fs\n", sorts[i], ((double)(clockEnd - clockStart) / CLOCKS_PER_SEC));
		copyTab(cTab, firstTab, n);
	}

	freeTab(firstTab);
	freeTab(cTab);

	return 0;
}

void TQuickSort(int* tab, int nSize) {
	QuickSort(tab, 0, nSize - 1);
}

void TMergeSort1(int* tab, int nSize) {
	int* L = createTab(nSize / 2 + 1);
	int* P = createTab(nSize - (nSize / 2));
	if (!L || !P) {
		printf("Error while allocating memory!\n");
		return;
	}
	MergeSort1(tab, 0, nSize - 1, L, P);

	freeTab(L);
	freeTab(P);
}

void TMergeSort2(int* tab, int nSize) {
	int* M = createTab(nSize);
	if (!M) {
		printf("Error while allocating memory!\n");
		return;
	}

	MergeSort2(tab, 0, nSize - 1, M);

	freeTab(M);
}
