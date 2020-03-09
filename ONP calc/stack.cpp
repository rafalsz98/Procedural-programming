#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void makeEmptyStack(Stack** stack) {
	// Usunięcie wszystkich elementów ze stosu, jeśli takie są
	// Następnie ustawienie wskaźnika na NULL
	while (!isEmpty(*stack))
		del(stack);
	*stack = NULL;
}

void push(Stack** stack, char x) {
	// Dynamiczna alokacja pamięci dla elementu stosu
	Stack* p = (Stack*)malloc(sizeof(Stack));
	// Jeśli został poprawnie zalokowany, ustawiamy dla niego wartość i przypinamy go na sam szczyt stosu
	if (p)
	{
		p->item = x;
		p->next = *stack;
		*stack = p;
	}
	else
		printf("\nERROR: Stack overflow!!\n");
}

char pop(Stack** stack) {
	// Jeśli stos jest pusty zwracane jest 0
	if (isEmpty(*stack)) return 0;

	// Zapisanie znaku znajdującego się na szczycie stosu i usunięcie najwyższego elementu stosu
	char c = top(*stack);
	del(stack);
	return c;
}

char top(Stack* stack) {
	// Jeśli stos jest pusty, zwracane jest 0, inaczej najwyższy element stosu
	return isEmpty(stack) ? 0 : stack->item;
}

void del(Stack** stack) {
	// Jeśli stos nie jest pusty najwyższym elementem stosu staje się drugi, a pierwszy zostaje zwolniony z pamięci
	if (!isEmpty(*stack))
	{
		Stack* p = *stack;
		*stack = p->next;
		free(p); // zwolnienie pamięci
	}
	else
		printf("\nERROR: Stack underflow!!\n");
}

int  isEmpty(Stack* stack) {
	return !stack;
}
