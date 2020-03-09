#include "skoczek.h"
//#include "main.cpp"

#include <iostream>

int move(int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves)
{
	int coordx = x + pHorseMoves[move].x;
	int coordy = y + pHorseMoves[move].y;
	if (
		coordx >= nDim || coordx < 0 ||
		coordy >= nDim || coordy < 0 ||
		pChessBoard[coordx][coordy] != 0
		) return 0;
	*px = coordx;
	*py = coordy;
	return 1;
}

int root(int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves)
{
	pChessBoard[x][y] = moveNo;
	if (moveNo == nDim * nDim)
		return 1;

	int px, py;
	for (int i = 0; i <= EIGHTH; i++)
	{
		if (move(pChessBoard, nDim, i, x, y, &px, &py, pHorseMoves))
		{
			if (root(pChessBoard, nDim, moveNo + 1, px, py, pHorseMoves))
				return 1;
		}
	}
	pChessBoard[x][y] = 0;

	return 0;
}

int** createChessBoard(int nDim)
{
	int** chessBoard = (int**)calloc((nDim * nDim) + nDim, sizeof(int*));
	if (!chessBoard)
		return NULL;
	int* ptr = (int*)(chessBoard + nDim);

	for (int i = 0; i < nDim; i++)
		chessBoard[i] = (ptr + nDim * i);

	return chessBoard;
}

void freeChessBoard(int*** chessBoard)
{
	free(*chessBoard);
	*chessBoard = NULL;
}

void printChessBoard(int** chessBoard, int nDim)
{
	for (int i = 0; i < nDim; i++)
	{
		for (int j = 0; j < nDim; j++)
		{
			printf("%3d", chessBoard[i][j]);
		}
		printf("\n");
	}
}