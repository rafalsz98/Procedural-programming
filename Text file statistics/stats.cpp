#include "stats.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


void Visit(TreeElem* p, FILE* fout)
{
	fprintf(fout, "%s\tn: %d\tLines: ", p->pWord, p->nNo);
	PrintList(p->listHead, fout);
	fprintf(fout, "\n");
}

TreeElem* FindInsert(int nLine, TreeElem* p, char* word)
{
	if (!p)
	{
		TreeElem* tree = (TreeElem*)calloc(1, sizeof(TreeElem));
		if (!tree) return NULL;
		tree->pWord = (char*)calloc(strlen(word) + 1, sizeof(char));
		if (!tree->pWord)
		{
			free(tree);
			return NULL;
		}
		strcpy(tree->pWord, word);
		tree->nNo = 1;

		tree->listHead = CreateList();
		if (IsEmpty(tree->listHead) || LastListItem(tree->listHead) != nLine)
			Insert(tree->listHead, nLine);
		return tree;
	}

	switch (Compare(word, p->pWord))
	{
	case -1:
		p->pLeft = FindInsert(nLine, p->pLeft, word);
		break;
	case 1:
		p->pRight = FindInsert(nLine, p->pRight, word);
		break;
	case 0:
		p->nNo++;
		if (IsEmpty(p->listHead) || LastListItem(p->listHead) != nLine)
			Insert(p->listHead, nLine);
		break;
	}
	return p;

}

void inOrder(TreeElem* p, FILE* fout)
{
	if (p->pLeft)
		inOrder(p->pLeft, fout);
	Visit(p, fout);
	if (p->pRight)
		inOrder(p->pRight, fout);
}

void postOrder(TreeElem* p, FILE* fout)
{
	if (p->pLeft)
		postOrder(p->pLeft, fout);
	if (p->pRight)
		postOrder(p->pRight, fout);
	Visit(p, fout);
}

void preOrder(TreeElem* p, FILE* fout)
{
	Visit(p, fout);
	if (p->pLeft)
		preOrder(p->pLeft, fout);
	if (p->pRight)
		preOrder(p->pRight, fout);
}

TreeElem* FreeTree(TreeElem* p)
{
	if (p)
	{
		p->pLeft = FreeTree(p->pLeft);
		FreeTree(p->pRight);

		FreeList(p->listHead);
		free(p);
	}
	return NULL;
}

int Compare(char* p1, char* p2)
{
	char* w1 = (char*)calloc(strlen(p1) + 1, sizeof(char));
	if (!w1)
	{
		printf("Err: Alloc\n");
		return -3;
	}

	char* w2 = (char*)calloc(strlen(p2) + 1, sizeof(char));
	if (!w2)
	{
		printf("Err: Alloc\n");
		return -3;
	}

	strcpy(w1, p1);
	strcpy(w2, p2);

	_strlwr(w1);
	_strlwr(w2);

	int res = strcmp(w1, w2);
	free(w1);
	free(w2);
	return res;
}