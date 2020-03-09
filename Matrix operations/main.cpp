#include <iostream>
#include <time.h>

#include "matrix.h"

//#define _DEBUG_

using namespace std;
void ReadData(FILE* fin, double** pMatrix, double* pB, int nDim);

#ifdef _DEBUG_
void RandMatrix(double** pMatrix, int nDim);
#endif // _DEBUG_


int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: matrix.exe <txt file>");
		return -1;
	}

	// Odczyt pliku
	FILE* fin = NULL;
	if (!(fin = fopen(argv[1], "r"))) {
		printf("Can't access file!\n");
		return -2;
	}

	// Wczytanie rozmiaru nDim
	int nSize = 0;
	if (!fscanf(fin, "%d", &nSize)) {
		printf("Ups... Something went wrong!\n");
		return -1;
	}


	// Kreacja macierzy pMx: nDim x nDim
	double** pMx = NULL;
	if (!CreateMatrix(&pMx, nSize)) {
		printf("Error while allocating matrix!\n");
		return -1;
	}

	// Kreacja wektora wyrazów wolnych
	double* pB = (double*)malloc(sizeof(double) * nSize);
	if (!pB) {
		printf("Error while allocating memory!\n");
		return -1;
	}
	memset(pB, 0, sizeof(double) * nSize);

	// Wczytanie danych
	ReadData(fin, pMx, pB, nSize);


	// Obliczenie wyznacznika
	double det = Det(pMx, nSize);
	// Obrócenie macierzy (jeœli siê da)
	if (fabs(det) < 1e-14) {
		printf("\nDeterminant must be different than 0 to inverse matrix!\nNieskonczenie wiele rozwiazan\n");
		return -1;
	}

	double** pInv = NULL;
	if (!CreateMatrix(&pInv, nSize)) {
		printf("Error while allocating matrix!\n");
		return -1;
	}

	InverseMatrix(pInv, pMx, nSize, det);


	// Wektor rozwi¹zañ
	double* pRes = (double*)malloc(sizeof(double) * nSize);
	if (!pRes) {
		printf("Error while allocating memory!\n");
		return -1;
	}
	memset(pRes, 0, sizeof(double) * nSize);

	// Rozwi¹zanie uk³adu
	LayoutEqu(pInv, pB, pRes, nSize);

	// Wypisanie wyników
	printf("Wyniki ukladu rownan: \n");
	double* it = pRes;
	for (int i = 0; i < nSize; i++) {
		printf(" %.2f \n", *it++);
	}
	// Zwolnienie pamiêci
	fclose(fin);
	free(pB);
	free(pRes);
	DeleteMatrix(&pMx, nSize);
	DeleteMatrix(&pInv, nSize);
	return 0;
}

void ReadData(FILE* fin, double** pMatrix, double* b, int nDim) {
	for (int i = 0; i < nDim; i++) {
		double* col = *pMatrix++;
		for (int j = 0; j < nDim; j++) {
			if (!fscanf(fin, "%lf", col++)) {
				printf("Ups... Wrong format \n");
				return;
			}
		}
		if (!fscanf(fin, "%lf", b++)) {
			printf("Ups... Wrong format \n");
			return;
		}
	}
}

#ifdef _DEBUG_
void RandMatrix(double** pMatrix, int nDim) {
	//srand((unsigned)time(NULL));
	srand(1);
	for (int i = 0; i < nDim; i++) {
		for (int j = 0; j < nDim; j++) {
			pMatrix[i][j] = rand() % 5 + 1.0 * (rand() % 100) / 100;
		}
	}
}
#endif // _DEBUG_
