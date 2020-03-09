#pragma once

#include "IntList.h"
#include <stdio.h>

typedef struct TreeElem
{
	int nNo; // ilosc wystapien w tekscie
	char* pWord; // s�owo (tak jak identyfikator w programie(du�e i ma�e litery sie nie r�ni�))
	IntList* listHead;

	TreeElem* pLeft; // po lewej stronie mniejsze slowo leksykalnie
	TreeElem* pRight;
} TreeElem;

void Visit(TreeElem* p, FILE* fout);
TreeElem* FindInsert(int x, TreeElem* p, char* word);
void inOrder(TreeElem* p, FILE* fout);
void postOrder(TreeElem* p, FILE* fout);
void preOrder(TreeElem* p, FILE* fout);
TreeElem* FreeTree(TreeElem* p);
int Compare(char* p1, char* p2);

