#include <stdio.h>
#include <stdlib.h>
#include <math.h> // zawiera sta³a INFINITY

#include "DoubleStack.h"

void dmakeEmptyStack(DoubleStack** stack) {
	// Usuniêcie wszystkich elementów ze stosu, jeœli takie s¹
	// Nastêpnie ustawienie wskaŸnika na NULL
	while (!disEmpty(*stack))
		ddel(stack);
	*stack = NULL;
}

void dpush(DoubleStack** stack, double x) {
	// Dynamiczna alokacja pamiêci dla elementu stosu
	DoubleStack* p = (DoubleStack*)malloc(sizeof(DoubleStack));
	// Jeœli zosta³ poprawnie zalokowany, ustawiamy dla niego wartoœæ i przypinamy go na sam szczyt stosu
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
	// Jeœli stos jest pusty zwracane jest -INFINITY
	if (disEmpty(*stack)) {
		printf("\nStack underflow!! (dpop)\n");
		return -INFINITY;
	}

	// Zapisanie znaku znajduj¹cego siê na szczycie stosu i usuniêcie najwy¿szego elementu stosu
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
	// Jeœli stos jest pusty, zwracane jest -INFINITY, inaczej najwy¿szy element stosu
	//return disEmpty( stack ) ? -INFINITY : stack->item;
}

void ddel(DoubleStack** stack) {
	// Jeœli stos nie jest pusty najwy¿szym elementem stosu staje siê drugi, a pierwszy zostaje zwolniony z pamiêci
	if (!disEmpty(*stack))
	{
		DoubleStack* p = *stack;
		*stack = p->next;
		free(p); // zwolnienie pamiêci
	}
	else
		printf("\nERROR: Stack underflow!!\n");
}

int  disEmpty(DoubleStack* stack) {
	return !stack;
}