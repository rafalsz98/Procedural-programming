#ifndef ONP_H
#define ONP_H

void skipSpaces(); // Pomija spacje w strumieniu wejœcia
double getNum(); // Znajduje liczbê ze strumienia wejœcia i zwraca j¹ jako typ double
int isDigit(char c); // Sprawdza czy znak c jest znakiem liczby
int prior(char cOper); // Zwraca priorytet operatora
double calc(double oper1, double oper2, char cOperator); // Oblicza i zwraca wartoœæ wyra¿enia
int isPrior(char cOper);
char getOper();

double ONP(); // G³ówna funkcja kontroluj¹ca przebieg dzia³ania

#endif // !ONP_H