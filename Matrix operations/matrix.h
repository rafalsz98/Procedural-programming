#ifndef MATRIX_H

int CreateMatrix(double*** pTab, int nSize);  // 0 error, 1 ok
void DeleteMatrix(double*** pTab, int nSize);

void TransMatrix(double** pTab, int nDim);

void InverseMatrix(double** pInv, double** pTab, int nSize, double det);
double Det(double** pTab, int nSize); //rozwiniêcie wzgl 0-go wiersza (rekurencja // indeks dla 2x2)
void LayoutEqu(double** pInv, double* pB, double* pRes, int nSize); //uk³ad równañ ; pB - wektor wyrazów wolnych
void PrintMatrix(double** pTab, int nSize);

#endif // !MATRIX_H
