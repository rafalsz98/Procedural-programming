#include <iostream>
#include <stdio.h>
#include <math.h>

#include "onp.h"
#include "stack.h"
#include "doubleStack.h"

#define DOT '.'

using namespace std;


void skipSpaces() {
	char c;
	// P�tla zako�czy si� gdy znak c b�dzie r�ny od spacji, wtedy znak ten zostaje zwr�cony na strumie� wej�cia
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}

double getNum() {
	// Pomini�cie spacji
	skipSpaces();
	char c;
	double num = 0.0; // Zmienna reprezentuj�ca cz�� ca�kowit� liczby
	int sign = 1;
	if ((c = getchar()) == '-')
		sign = -1;
	else if (c != '+')
		ungetc(c, stdin);

	// Dop�ki getchar pobiera znak cyfry obliczana jest cz�� ca�kowita liczby
	while (isDigit(c = getchar())) {
		num = num * 10 + (c - '0');
	}

	// Je�li znakiem kt�ry przerwa� poprzedni� p�tle jest sta�a DOT, to jest to cz�� liczby po przecinku 
	if (c == DOT) {
		double k = 0.1; // Wskazuje na aktualne miejsce po przecinku
		while (isDigit(c = getchar())) {
			num = num + ((c - '0') * k);
			k /= 10; // Dzi�ki tej operacji kolejna pobrana liczba b�dzie mniej znacz�ca
		}
	}
	// Zwr�cenie ostatniego pobranego znaku na strumie� wyj�cia i zwr�cenie z funkcji otrzymanej liczby
	ungetc(c, stdin);
	return num * sign;
}

int isDigit(char c) {
	return (c >= '0') && (c <= '9');
}

int prior(char cOper) {
	switch (cOper) {
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}

int isPrior(char cOper) {
	switch (cOper) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '(':
	case ')': return 1;
	}
	return 0;
}

double calc(double oper1, double oper2, char cOperator) {
	switch (cOperator) {
	case '+': return oper1 + oper2;
	case '-': return oper1 - oper2;
	case '*': return oper1 * oper2;
	case '/':
		if (fabs(oper2) > 1e-14)
			return oper1 / oper2;
		cout << "\nError: division by 0!\n";
		break;
	case '^': return pow(oper1, oper2);
	}
	return -INFINITY;
}

char getOper() {
	skipSpaces();
	return getchar();
}

double ONP() {
	char c;
	// Inicjalizacja stacku przeznaczonego dla char'�w i dla double'i
	Stack* stack = NULL;
	DoubleStack* doubleStack = NULL;
	makeEmptyStack(&stack);
	dmakeEmptyStack(&doubleStack);

	// Najpierw sprawdzane jest, czy pierwszym znakiem jest minus lub plus. Je�li jest to minus, na stos dok�adana jest liczba 0 i znak.
	// Zapewni to poprawn� zamian� na ONP (np. -5 zostanie zamienione na 0 5 -)
	if ((c = getOper()) == '-') {
		dpush(&doubleStack, 0.0);
		push(&stack, c);
	}
	else if (c != '+') {
		ungetc(c, stdin);
	}

	while ((c = getOper())) {
		// Je�li program natrafi� na cyfr� lub kropk�, znak ten zostaje zwr�cony i uruchomiona zostaje funkcja getNum()
		// kt�ra od razu wrzuci na stos liczbowy znalezion� liczb�, a kolejna instrukcj� j� wypisze na wyj�cie
		if (isDigit(c) || c == DOT) {
			ungetc(c, stdin);
			dpush(&doubleStack, getNum());
		}
		// Poni�szy blok wykonywany jest, gdy program natrafi� na znak operatora lub inny nieprawid�owy znak.
		else if (isPrior(c)) {
			switch (c) {
			case '(':
				// Nawias otwieraj�cy zawsze na stos, dodatkowo sprawdzany jest znak nast�puj�cy zaraz po nawiasie (z wykluczeniem spacji)
				// Powtarzamy operacj� z pocz�tku dzia�ania funkcji
				push(&stack, c);
				if ((c = getOper()) == '-') {
					dpush(&doubleStack, 0.0);
					push(&stack, c);
				}
				else if (c != '+')
					ungetc(c, stdin);
				break;
			case ')':
				// Je�li znakiem jest nawias zamykaj�cy to w��czana jest p�tla kt�ra dzia�a a� do znalezienia nawiasu otwieraj�cego na stosie
				// Przy ka�dym wykonaniu p�tli na stos liczbowy wrzucany jest wynik operacji dw�ch ostatnich liczb na stosie
				// z operatorem na stosie operator�w
				// Operator ten jest wypisywany i zdejmowany ze stosu
				while ((c = pop(&stack)) != '(') {
					// Je�li ostatnim znakiem na stosie nie jest nawias otwieraj�cy to wej�ciowy format by� z�y
					if (c != '(' && isEmpty(stack)) {
						cout << "Wrong format!";
						return -INFINITY;
					}
					double x = dpop(&doubleStack);
					dpush(&doubleStack, calc(dpop(&doubleStack), x, c));
				}
				break;
			default:
				// Niezale�nie od operatora arytmetycznego, poni�sza instrukcja zawsze b�dzie prawdziwa
				// Dop�ki operatory na stosie b�d� mia�y wi�kszy lub r�wny priorytet od znaku z wej�cia: 
				// - na stos liczbowy b�dzie wrzucany wynik dzia�ania dw�ch ostatnich element�w stosu liczbowego i operatora ze stosu operator�w
				// - znak ze stosu operator�w zostanie usuni�ty
				// Po wyj�ciu z p�tli obecny znak musi zosta� wpisany do stosu operator�w
				while (prior(c) <= prior(top(stack))) {
					double x = dpop(&doubleStack);
					dpush(&doubleStack, calc(dpop(&doubleStack), x, pop(&stack)));
				}
				push(&stack, c);
				break;
			}
		}
		// Je�li znak nie zosta� przewidziany to przerywa on p�tle while
		else
			break;
	}

	// Je�li w stosie operator�w zosta� jaki� znak, zostanie on wypisany oraz zostanie wykonana operacja arytmetyczna
	while (!isEmpty(stack)) {
		double x = dpop(&doubleStack);
		dpush(&doubleStack, calc(dpop(&doubleStack), x, pop(&stack)));
	}

	// Element szczytowy stosu liczbowego jest jednocze�nie wynikiem ca�ego r�wnania
	double res = dpop(&doubleStack);
	if (res == -INFINITY) printf("Wrong format!");

	// Wywo�anie funkcji zwalniaj�cych pami��
	makeEmptyStack(&stack);
	dmakeEmptyStack(&doubleStack);
	return res;
}
