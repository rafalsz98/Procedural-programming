#include "matrix.h"
#include <stdlib.h>
#include <iostream>

// Private ------- //
void Complement(double** pTab0, double** pTabI, int nRow, int nCol, int nDim) {
	// Dzia�a przy za�o�eniu, �e pTabI jest macierz� o wymiarze o 1 mniejszym od pTab0

	//int col = 0; // Aktualna kolumna, do kt�rej zapisujemy

	double** tab0Row = pTab0;
	double** tabIRow = pTabI;

	// P�tl� przechodzimy po ca�ej macierzy
	for (int i = 0; i < nDim; i++, tab0Row++) {
		if (i == nRow) continue;

		double* tab0Col = *tab0Row;
		double* tabICol = *tabIRow;

		for (int j = 0; j < nDim; j++, tab0Col++) {
			if (j == nCol) 	continue;
			*tabICol++ = *tab0Col;
		}
		tabIRow++;
	}
}

void ComplMatrix(double** pTabD, double** pTab, int nDim) {
	// Tworzy macierz dope�nie� algebraicznych
	// Dzia�a przy za�o�eniu, �e pTabD ma taki sam wymiar jak pTab


	// Macierz tymczasowa, stopie� o 1 mniejszy od pTab do przechowywania macierzy z wyci�tymi wierszami i kolumnami
	double** complMx = NULL;
	if (!CreateMatrix(&complMx, nDim - 1)) {
		printf("Error while allocating matrix!\n");
		return;
	}

	double** DRow = pTabD;
	for (int i = 0; i < nDim; i++) {
		double* DCol = *DRow++;
		int sign = (i % 2) ? -1 : 1;

		for (int j = 0; j < nDim; j++) {
			// Wycinamy z macierzy pTab wiersz i, kolumn� j
			Complement(pTab, complMx, i, j, nDim);
			// Liczymy wyznacznik z powsta�ej macierzy, mno�ymy przez sign i zmieniamy sign na znak przeciwny
			*DCol++ = sign * Det(complMx, nDim - 1);
			sign = -sign;
		}
	}

	// Wyczyszczenie pami�ci
	DeleteMatrix(&complMx, nDim - 1);
}
// --------------- //

int CreateMatrix(double*** pTab, int nSize) {
	// Alokuje pami�� dla tablicy dwuwymiarowej, je�li si� nie powiod�o zwraca 0
	*pTab = (double**)malloc(sizeof(double*) * nSize);
	memset(*pTab, 0, sizeof(double*) * nSize);
	if (!*pTab) return 0;

	// Dla ka�dego wska�nika w powsta�ej tablicy alokuje pami�� i zeruje tablice
	double** row = *pTab;
	for (int i = 0; i < nSize; i++) {
		*row = (double*)malloc(sizeof(double) * nSize);
		if (!*row) return 0;
		memset(*row, 0, sizeof(double) * nSize);
		row++;
	}
	return 1;
}

void DeleteMatrix(double*** pTab, int nSize) {
	// Zwalnia pami�� ze wszystkich element�w tablicy wska�nik�w
	double** v = *pTab;
	for (int i = 0; i < nSize; i++) {
		free(*v++);
	}
	// Nast�pnie zwalnia t� tablic� wska�nik�w, a wska�nik na ni� ustawia na NULL
	free(*pTab);
	*pTab = NULL;
}

void TransMatrix(double** pTab, int nDim) {
	double** row = pTab;

	// Przej�cie po elementach znajduj�cych si� po prawej od prz�k�tnej
	for (int i = 0; i < nDim - 1; i++) {
		double* col = *row++ + i + 1;
		for (int j = i + 1; j < nDim; j++) {
			// Zamiana miejscami
			double tmp = *col;
			*col++ = pTab[j][i];
			pTab[j][i] = tmp;
		}
	}
}

void InverseMatrix(double** pInv, double** pTab, int nSize, double det) {
	// Stworzenie nowej macierzy o wymiarze nSize, kt�ra b�dzie transponowan� macierz� dope�nie� macierzy pTab
	double** complMx = NULL;
	if (!CreateMatrix(&complMx, nSize)) {
		printf("Error while allocating matrix!\n");
		return;
	}

	ComplMatrix(complMx, pTab, nSize);

	TransMatrix(complMx, nSize);

	double** row = pInv;
	double** complRow = complMx;
	for (int i = 0; i < nSize; i++) {
		double* col = *row++;
		double* complCol = *complRow++;
		for (int j = 0; j < nSize; j++) {
			// Dla ka�dego elementu macierzy wynikiem jest pomno�enie odwrotno�ci wyznacznika przez element macierzy complMx
			*col++ = (1. / det) * (*complCol++);
		}
	}

	// Zwolnienie pami�ci
	DeleteMatrix(&complMx, nSize);

}

double Det(double** pTab, int nSize) {
	double res = 0;

	// Przypadek bazowy, dla macierzy o wymiarze 1
	if (nSize == 1)
		return **pTab;

	// Nowa tymczasowa macierz do przechowywania macierzy pTab z wyci�tymi wierszami i kolumnami
	double** coMx = NULL;
	if (!CreateMatrix(&coMx, nSize - 1)) {
		printf("Error while allocating matrix!\n");
		return 0;
	}


	int sign = 1;

	double* col = *pTab;
	for (int i = 0; i < nSize; i++) {
		// Wyci�cie wiersza 0 i kolumny i
		Complement(pTab, coMx, 0, i, nSize);
		// Rekurencyjne wywo�anie wyznacznika dla wyci�tej macierzy i zmiana znaku na przeciwny
		res = res + sign * (*col++) * Det(coMx, nSize - 1);
		sign = -sign;
	}

	// Zwolnienie pami�ci i zwrot warto�ci
	DeleteMatrix(&coMx, nSize - 1);
	return res;
}

void LayoutEqu(double** pInv, double* pB, double* pRes, int nSize) {
	double* resCol = pRes;
	double** invRow = pInv;
	for (int i = 0; i < nSize; i++) {
		double* pbCol = pB;
		double* invCol = *invRow;
		for (int j = 0; j < nSize; j++) {
			// Mno�enie macierzy przez wektor
			*resCol += ((*invCol++) * (*pbCol++));
		}
		resCol++;
		invRow++;
	}
}

void PrintMatrix(double** pTab, int nSize) {
	// Wypisanie wszystkich element�w macierzy pTab
	for (int i = 0; i < nSize; i++) {
		double* p = *pTab++;
		for (int j = 0; j < nSize; j++) {
			printf(" %.2f ", *p++);
		}
		printf("\n");
	}
}
