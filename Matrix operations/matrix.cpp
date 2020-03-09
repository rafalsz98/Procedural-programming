#include "matrix.h"
#include <stdlib.h>
#include <iostream>

// Private ------- //
void Complement(double** pTab0, double** pTabI, int nRow, int nCol, int nDim) {
	// Dzia³a przy za³o¿eniu, ¿e pTabI jest macierz¹ o wymiarze o 1 mniejszym od pTab0

	//int col = 0; // Aktualna kolumna, do której zapisujemy

	double** tab0Row = pTab0;
	double** tabIRow = pTabI;

	// Pêtl¹ przechodzimy po ca³ej macierzy
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
	// Tworzy macierz dope³nieñ algebraicznych
	// Dzia³a przy za³o¿eniu, ¿e pTabD ma taki sam wymiar jak pTab


	// Macierz tymczasowa, stopieñ o 1 mniejszy od pTab do przechowywania macierzy z wyciêtymi wierszami i kolumnami
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
			// Wycinamy z macierzy pTab wiersz i, kolumnê j
			Complement(pTab, complMx, i, j, nDim);
			// Liczymy wyznacznik z powsta³ej macierzy, mno¿ymy przez sign i zmieniamy sign na znak przeciwny
			*DCol++ = sign * Det(complMx, nDim - 1);
			sign = -sign;
		}
	}

	// Wyczyszczenie pamiêci
	DeleteMatrix(&complMx, nDim - 1);
}
// --------------- //

int CreateMatrix(double*** pTab, int nSize) {
	// Alokuje pamiêæ dla tablicy dwuwymiarowej, jeœli siê nie powiod³o zwraca 0
	*pTab = (double**)malloc(sizeof(double*) * nSize);
	memset(*pTab, 0, sizeof(double*) * nSize);
	if (!*pTab) return 0;

	// Dla ka¿dego wskaŸnika w powsta³ej tablicy alokuje pamiêæ i zeruje tablice
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
	// Zwalnia pamiêæ ze wszystkich elementów tablicy wskaŸników
	double** v = *pTab;
	for (int i = 0; i < nSize; i++) {
		free(*v++);
	}
	// Nastêpnie zwalnia t¹ tablicê wskaŸników, a wskaŸnik na ni¹ ustawia na NULL
	free(*pTab);
	*pTab = NULL;
}

void TransMatrix(double** pTab, int nDim) {
	double** row = pTab;

	// Przejœcie po elementach znajduj¹cych siê po prawej od przêk¹tnej
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
	// Stworzenie nowej macierzy o wymiarze nSize, która bêdzie transponowan¹ macierz¹ dope³nieñ macierzy pTab
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
			// Dla ka¿dego elementu macierzy wynikiem jest pomno¿enie odwrotnoœci wyznacznika przez element macierzy complMx
			*col++ = (1. / det) * (*complCol++);
		}
	}

	// Zwolnienie pamiêci
	DeleteMatrix(&complMx, nSize);

}

double Det(double** pTab, int nSize) {
	double res = 0;

	// Przypadek bazowy, dla macierzy o wymiarze 1
	if (nSize == 1)
		return **pTab;

	// Nowa tymczasowa macierz do przechowywania macierzy pTab z wyciêtymi wierszami i kolumnami
	double** coMx = NULL;
	if (!CreateMatrix(&coMx, nSize - 1)) {
		printf("Error while allocating matrix!\n");
		return 0;
	}


	int sign = 1;

	double* col = *pTab;
	for (int i = 0; i < nSize; i++) {
		// Wyciêcie wiersza 0 i kolumny i
		Complement(pTab, coMx, 0, i, nSize);
		// Rekurencyjne wywo³anie wyznacznika dla wyciêtej macierzy i zmiana znaku na przeciwny
		res = res + sign * (*col++) * Det(coMx, nSize - 1);
		sign = -sign;
	}

	// Zwolnienie pamiêci i zwrot wartoœci
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
			// Mno¿enie macierzy przez wektor
			*resCol += ((*invCol++) * (*pbCol++));
		}
		resCol++;
		invRow++;
	}
}

void PrintMatrix(double** pTab, int nSize) {
	// Wypisanie wszystkich elementów macierzy pTab
	for (int i = 0; i < nSize; i++) {
		double* p = *pTab++;
		for (int j = 0; j < nSize; j++) {
			printf(" %.2f ", *p++);
		}
		printf("\n");
	}
}
