#ifndef MATRIX_H

int CreateMatrix(double*** pTab, int nSize);  // 0 error, 1 ok
void DeleteMatrix(double*** pTab, int nSize);

void TransMatrix(double** pTab, int nDim);

void InverseMatrix(double** pInv, double** pTab, int nSize, double det);
double Det(double** pTab, int nSize); //rozwini�cie wzgl 0-go wiersza (rekurencja // indeks dla 2x2)
void LayoutEqu(double** pInv, double* pB, double* pRes, int nSize); //uk�ad r�wna� ; pB - wektor wyraz�w wolnych
void PrintMatrix(double** pTab, int nSize);

#endif // !MATRIX_H
