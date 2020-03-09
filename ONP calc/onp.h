#ifndef ONP_H
#define ONP_H

void skipSpaces(); // Pomija spacje w strumieniu wej�cia
double getNum(); // Znajduje liczb� ze strumienia wej�cia i zwraca j� jako typ double
int isDigit(char c); // Sprawdza czy znak c jest znakiem liczby
int prior(char cOper); // Zwraca priorytet operatora
double calc(double oper1, double oper2, char cOperator); // Oblicza i zwraca warto�� wyra�enia
int isPrior(char cOper);
char getOper();

double ONP(); // G��wna funkcja kontroluj�ca przebieg dzia�ania

#endif // !ONP_H