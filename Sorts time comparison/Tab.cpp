#include "Tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

int* createTab(int nSize) {
	int* tab = (int*)malloc(sizeof(int) * nSize);
	if (!tab)
		return NULL;
	initTab(tab, nSize, 0);
	return tab;
}

void freeTab(int* pTab) {
	free(pTab);
}

void initTab(int* pTab, int nSize, int nVal) {
	memset(pTab, nSize, nVal);
}

void randInit(int* pTab, int nSize) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < nSize; i++) {
		pTab[i] = rand() % nSize;
	}
}

void copyTab(int* pTabTo, int* pTabFrom, int nSize) {
	memcpy(pTabTo, pTabFrom, nSize * sizeof(int));
}