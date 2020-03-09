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
	// Pêtla zakoñczy siê gdy znak c bêdzie ró¿ny od spacji, wtedy znak ten zostaje zwrócony na strumieñ wejœcia
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}

double getNum() {
	// Pominiêcie spacji
	skipSpaces();
	char c;
	double num = 0.0; // Zmienna reprezentuj¹ca czêœæ ca³kowit¹ liczby
	int sign = 1;
	if ((c = getchar()) == '-')
		sign = -1;
	else if (c != '+')
		ungetc(c, stdin);

	// Dopóki getchar pobiera znak cyfry obliczana jest czêœæ ca³kowita liczby
	while (isDigit(c = getchar())) {
		num = num * 10 + (c - '0');
	}

	// Jeœli znakiem który przerwa³ poprzedni¹ pêtle jest sta³a DOT, to jest to czêœæ liczby po przecinku 
	if (c == DOT) {
		double k = 0.1; // Wskazuje na aktualne miejsce po przecinku
		while (isDigit(c = getchar())) {
			num = num + ((c - '0') * k);
			k /= 10; // Dziêki tej operacji kolejna pobrana liczba bêdzie mniej znacz¹ca
		}
	}
	// Zwrócenie ostatniego pobranego znaku na strumieñ wyjœcia i zwrócenie z funkcji otrzymanej liczby
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
	// Inicjalizacja stacku przeznaczonego dla char'ów i dla double'i
	Stack* stack = NULL;
	DoubleStack* doubleStack = NULL;
	makeEmptyStack(&stack);
	dmakeEmptyStack(&doubleStack);

	// Najpierw sprawdzane jest, czy pierwszym znakiem jest minus lub plus. Jeœli jest to minus, na stos dok³adana jest liczba 0 i znak.
	// Zapewni to poprawn¹ zamianê na ONP (np. -5 zostanie zamienione na 0 5 -)
	if ((c = getOper()) == '-') {
		dpush(&doubleStack, 0.0);
		push(&stack, c);
	}
	else if (c != '+') {
		ungetc(c, stdin);
	}

	while ((c = getOper())) {
		// Jeœli program natrafi³ na cyfrê lub kropkê, znak ten zostaje zwrócony i uruchomiona zostaje funkcja getNum()
		// która od razu wrzuci na stos liczbowy znalezion¹ liczbê, a kolejna instrukcj¹ j¹ wypisze na wyjœcie
		if (isDigit(c) || c == DOT) {
			ungetc(c, stdin);
			dpush(&doubleStack, getNum());
		}
		// Poni¿szy blok wykonywany jest, gdy program natrafi³ na znak operatora lub inny nieprawid³owy znak.
		else if (isPrior(c)) {
			switch (c) {
			case '(':
				// Nawias otwieraj¹cy zawsze na stos, dodatkowo sprawdzany jest znak nastêpuj¹cy zaraz po nawiasie (z wykluczeniem spacji)
				// Powtarzamy operacjê z pocz¹tku dzia³ania funkcji
				push(&stack, c);
				if ((c = getOper()) == '-') {
					dpush(&doubleStack, 0.0);
					push(&stack, c);
				}
				else if (c != '+')
					ungetc(c, stdin);
				break;
			case ')':
				// Jeœli znakiem jest nawias zamykaj¹cy to w³¹czana jest pêtla która dzia³a a¿ do znalezienia nawiasu otwieraj¹cego na stosie
				// Przy ka¿dym wykonaniu pêtli na stos liczbowy wrzucany jest wynik operacji dwóch ostatnich liczb na stosie
				// z operatorem na stosie operatorów
				// Operator ten jest wypisywany i zdejmowany ze stosu
				while ((c = pop(&stack)) != '(') {
					// Jeœli ostatnim znakiem na stosie nie jest nawias otwieraj¹cy to wejœciowy format by³ z³y
					if (c != '(' && isEmpty(stack)) {
						cout << "Wrong format!";
						return -INFINITY;
					}
					double x = dpop(&doubleStack);
					dpush(&doubleStack, calc(dpop(&doubleStack), x, c));
				}
				break;
			default:
				// Niezale¿nie od operatora arytmetycznego, poni¿sza instrukcja zawsze bêdzie prawdziwa
				// Dopóki operatory na stosie bêd¹ mia³y wiêkszy lub równy priorytet od znaku z wejœcia: 
				// - na stos liczbowy bêdzie wrzucany wynik dzia³ania dwóch ostatnich elementów stosu liczbowego i operatora ze stosu operatorów
				// - znak ze stosu operatorów zostanie usuniêty
				// Po wyjœciu z pêtli obecny znak musi zostaæ wpisany do stosu operatorów
				while (prior(c) <= prior(top(stack))) {
					double x = dpop(&doubleStack);
					dpush(&doubleStack, calc(dpop(&doubleStack), x, pop(&stack)));
				}
				push(&stack, c);
				break;
			}
		}
		// Jeœli znak nie zosta³ przewidziany to przerywa on pêtle while
		else
			break;
	}

	// Jeœli w stosie operatorów zosta³ jakiœ znak, zostanie on wypisany oraz zostanie wykonana operacja arytmetyczna
	while (!isEmpty(stack)) {
		double x = dpop(&doubleStack);
		dpush(&doubleStack, calc(dpop(&doubleStack), x, pop(&stack)));
	}

	// Element szczytowy stosu liczbowego jest jednoczeœnie wynikiem ca³ego równania
	double res = dpop(&doubleStack);
	if (res == -INFINITY) printf("Wrong format!");

	// Wywo³anie funkcji zwalniaj¹cych pamiêæ
	makeEmptyStack(&stack);
	dmakeEmptyStack(&doubleStack);
	return res;
}
