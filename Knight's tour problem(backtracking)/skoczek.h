#pragma once

enum
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
	SIXTH,
	SEVENTH,
	EIGHTH
};

struct Point
{
	int x;
	int y;
};

int move(int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves);
int root(int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves);
int** createChessBoard(int nDim);
void freeChessBoard(int*** pchessboard);
void printChessBoard(int** pchessboard, int nDim);