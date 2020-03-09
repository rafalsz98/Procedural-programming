#ifndef DOUBLESTACK_H
#define DOUBLESTACK_H

typedef struct DoubleStack {
	double item;
	DoubleStack* next;
} DoubleStack;

void dmakeEmptyStack(DoubleStack** stack);
void dpush(DoubleStack** stack, double x);
double dpop(DoubleStack** stack);
double dtop(DoubleStack* stack);
void ddel(DoubleStack** stack);
int  disEmpty(DoubleStack* stack);

#endif // !DOUBLESTACK_H


