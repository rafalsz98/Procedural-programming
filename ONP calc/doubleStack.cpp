#include <stdio.h>
#include <stdlib.h>
#include <math.h> // zawiera sta�a INFINITY

#include "DoubleStack.h"

void dmakeEmptyStack(DoubleStack** stack) {
	// Usuni�cie wszystkich element�w ze stosu, je�li takie s�
	// Nast�pnie ustawienie wska�nika na NULL
	while (!disEmpty(*stack))
		ddel(stack);
	*stack = NULL;
}

void dpush(DoubleStack** stack, double x) {
	// Dynamiczna alokacja pami�ci dla elementu stosu
	DoubleStack* p = (DoubleStack*)malloc(sizeof(DoubleStack));
	// Je�li zosta� poprawnie zalokowany, ustawiamy dla niego warto�� i przypinamy go na sam szczyt stosu
	if (p)
	{
		p->item = x;
		p->next = *stack;
		*stack = p;
	}
	else
		printf("\nERROR: Stack overflow!!\n");
}

double dpop(DoubleStack** stack) {
	// Je�li stos jest pusty zwracane jest -INFINITY
	if (disEmpty(*stack)) {
		printf("\nStack underflow!! (dpop)\n");
		return -INFINITY;
	}

	// Zapisanie znaku znajduj�cego si� na szczycie stosu i usuni�cie najwy�szego elementu stosu
	double c = dtop(*stack);
	ddel(stack);
	return c;
}

double dtop(DoubleStack* stack) {
	if (disEmpty(stack)) {
		printf("\nStack underflow!! (dtop)");
		return -INFINITY;
	}
	return stack->item;
	// Je�li stos jest pusty, zwracane jest -INFINITY, inaczej najwy�szy element stosu
	//return disEmpty( stack ) ? -INFINITY : stack->item;
}

void ddel(DoubleStack** stack) {
	// Je�li stos nie jest pusty najwy�szym elementem stosu staje si� drugi, a pierwszy zostaje zwolniony z pami�ci
	if (!disEmpty(*stack))
	{
		DoubleStack* p = *stack;
		*stack = p->next;
		free(p); // zwolnienie pami�ci
	}
	else
		printf("\nERROR: Stack underflow!!\n");
}

int  disEmpty(DoubleStack* stack) {
	return !stack;
}