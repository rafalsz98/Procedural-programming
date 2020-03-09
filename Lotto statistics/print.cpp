#include "print.h"
#include "defs.h"

#include <stdio.h>
#include <stdlib.h>
//#include <iostream>

using namespace std;
#define MAXCHARLENGTH 15


void PrintSex(FILE* fout, Player* p);
void PrintDate(FILE* fout, Player* p);
void PrintHour(FILE* fout, Player* p);
void PrintBets(FILE* fout, int** pBets, int pBetsSize);


//*** Private ***//
void PrintSex(FILE* fout, Player* p) {
	if (p->pSex == MALE)
		fprintf(fout, "Male");
	else
		fprintf(fout, "Female");
}
void PrintDate(FILE* fout, Player* p) {
	switch (p->pDate.weekDay) {
	case mon:
		fprintf(fout, "Monday");
		break;
	case tue:
		fprintf(fout, "Tuesday");
		break;
	case wed:
		fprintf(fout, "Wednesday");
		break;
	case thu:
		fprintf(fout, "Thursday");
		break;
	case fri:
		fprintf(fout, "Friday");
		break;
	case sat:
		fprintf(fout, "Saturday");
		break;
	case sun:
		fprintf(fout, "Sunday");
		break;
	}
	if (p->pDate.day < 10)
		fprintf(fout, "  0%d ", p->pDate.day);
	else
		fprintf(fout, "  %d ", p->pDate.day);

	switch (p->pDate.monthName) {
	case Jan:
		fprintf(fout, "January");
		break;
	case Feb:
		fprintf(fout, "February");
		break;
	case Mar:
		fprintf(fout, "March");
		break;
	case Apr:
		fprintf(fout, "April");
		break;
	case May:
		fprintf(fout, "May");
		break;
	case Jun:
		fprintf(fout, "June");
		break;
	case Jul:
		fprintf(fout, "July");
		break;
	case Aug:
		fprintf(fout, "August");
		break;
	case Sep:
		fprintf(fout, "September");
		break;
	case Oct:
		fprintf(fout, "October");
		break;
	case Nov:
		fprintf(fout, "November");
		break;
	case Dec:
		fprintf(fout, "December");
		break;
	}
	fprintf(fout, " %d", p->pDate.year);
}
void PrintHour(FILE* fout, Player* p) {
	fprintf(fout, "%d:", p->hour);
	if (p->minute < 10)
		fputc('0', fout);
	fprintf(fout, "%d", p->minute);
}
void PrintBets(FILE* fout, int** pBets, int pBetsSize) {
	for (int i = 0; i < pBetsSize; i++) {
		for (int j = 0; j < MAXBETS; j++) {
			fprintf(fout, "%3d\t", pBets[i][j]);
		}
		fprintf(fout, "\n");
	}
}
//***        ***//

void PrintResults(int* pNums50, Player** pPlayers, int nPlayersNo) {
#ifndef DEBUG
	FILE* fout = fopen(RESFILENAME, "w");
	if (!fout) {
		printf("Couldn't open file\n");
		return;
	}
#endif // !DEBUG
#ifdef DEBUG
	FILE* fout = stdout;
#endif // DEBUG



	for (int i = 0; i < nPlayersNo; i++) {
		fprintf(fout, "%s %s\t", (*pPlayers)->pLastName, (*pPlayers)->pFirstName);
		PrintSex(fout, (*pPlayers));
		fprintf(fout, " \t ");
		fprintf(fout, "%s \t ", (*pPlayers)->pesel);
		PrintHour(fout, (*pPlayers));
		fprintf(fout, " \t ");
		PrintDate(fout, (*pPlayers));
		fprintf(fout, "\n");
		PrintBets(fout, (*pPlayers)->betsArray, (*pPlayers)->betsSize);

		fprintf(fout, "\n");
		pPlayers++;
	}

	fprintf(fout, "----------------------------------------\n\tSTATS\n----------------------------------------\n");

	int tmp;
	for (int i = 1; i <= (LOTTOMAX / PRINT_COLS); i++)
	{
		for (int j = 0; j < PRINT_COLS; j++)
		{
			if ((tmp = i + (LOTTOMAX / PRINT_COLS) * j) < LOTTOMAX)
				fprintf(fout, "%2d:\t%2d  \t\t", tmp, pNums50[tmp]);
		}
		fprintf(fout, "\n");
	}
	if (tmp != LOTTOMAX - 1) {
		tmp = LOTTOMAX - 1;
		for (int i = 0; i < PRINT_COLS * 2; i++) {
			fprintf(fout, "\t");
		}
		fprintf(fout, "%2d:\t%2d", tmp, pNums50[tmp]);
	}

#ifndef DEBUG
	fclose(fout);
#endif // !DEBUG

}