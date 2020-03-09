#ifndef STACK_H
#define STACK_H


typedef struct Stack {
	char item;
	Stack* next;
} Stack;

void makeEmptyStack(Stack** stack);
void push(Stack** stack, char x);
char pop(Stack** stack);
char top(Stack* stack);
void del(Stack** stack);
int  isEmpty(Stack* stack);

#endif // !STACK_H