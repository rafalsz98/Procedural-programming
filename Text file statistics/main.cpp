#include "stats.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define BUFFER 128

using namespace std;

TreeElem* Read(char* fileIn);
int isDigit(char c);
int isLetter(char c);


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Usage: stats.exe <in file> <out file>");
		return -1;
	}
	TreeElem* root = Read(argv[1]);
	if (!root)
	{
		printf("Couldn't read data properly\n");
		return -1;
	}

	FILE* fout = fopen(argv[2], "w");
	if (!fout)
	{
		printf("Error: Open file for write!\n");
		return -1;
	}

#ifdef DEBUG
	inOrder(root, stdout);
#endif // DEBUG
#ifndef DEBUG
	inOrder(root, fout);
#endif // !DEBUG




	fclose(fout);
	return 0;

}

TreeElem* Read(char* fileIn)
{
	FILE* fin = fopen(fileIn, "r");
	if (!fin)
	{
		printf("Error: Read file!\n");
		return NULL;
	}
	TreeElem* root = NULL;
	int currLine = 1;
	char c;

	while (!feof(fin) && (c = fgetc(fin)))
	{
		if (c == '\n') currLine++;
		else if (isLetter(c) || c == '_')
		{
			int i = 1;
			char word[BUFFER] = {c};
			while (
				(c = fgetc(fin)) && !feof(fin) && (
					isLetter(c) ||
					isDigit(c) ||
					c == '_'
					))
			{
				word[i] = c;
				i++;
			}
			if (c == '\n') currLine++;
			if (!root)
				root = FindInsert(currLine, root, word);
			else
				FindInsert(currLine, root, word);
		}
	}
	fclose(fin);
	return root;

}



int isDigit(char c)
{
	return c >= '0' && c <= '9';
}

int isLetter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}