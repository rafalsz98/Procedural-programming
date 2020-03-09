#include <iostream>
#include "skoczek.h"


//#define DEBUG
#define CHESSBOARD_SIZE 6
#define HORSEMOVES 8

using namespace std;

int main(int argc, char* argv[])
{
#ifndef DEBUG
	if (argc != 3)
	{
		printf("Usage: skoczek.exe <x0> <y0>\n");
		return -1;
	}
#endif // !DEBUG

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);

	// Sprawdzenie wprowadzonych liczb
	if (x < 0 || x >= CHESSBOARD_SIZE || y < 0 || y >= CHESSBOARD_SIZE)
	{
		printf("Wrong coordinates!\n");
		return -1;
	}

	int** chessBoard = createChessBoard(CHESSBOARD_SIZE);

	Point horseMoves[HORSEMOVES] = {
		{-2, 1},
		{-1, 2},
		{1, 2},
		{2, 1},
		{2, -1},
		{1, -2},
		{-1, -2},
		{-2, -1},
	};

	if (root(chessBoard, CHESSBOARD_SIZE, 1, x, y, horseMoves))
		printChessBoard(chessBoard, CHESSBOARD_SIZE);
	else
		printf("No solution!\n");
	freeChessBoard(&chessBoard);
	return 0;
}