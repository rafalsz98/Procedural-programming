#include "data.h"
#include <time.h>
#include <iostream>
#pragma warning(disable : 26812)

using namespace std;

int AllocAddMem(Player*** pTab, int nCurrSize);
int AllocAddBetsMem(int*** betsArray, int nCurrSize);


//*** Private functions ***///
int AllocAddMem(Player*** pTab, int nCurrSize)
{
	Player** copy = *pTab;
	*pTab = (Player**)realloc(*pTab, (nCurrSize + ALLOCPLAYER) * sizeof(Player*));
	if (!*pTab) {
		*pTab = copy;
		return 0;
	}
	memset(*pTab + nCurrSize, 0, ALLOCPLAYER * sizeof(Player*));
	return nCurrSize + ALLOCPLAYER;
}
int AllocAddBetsMem(int*** betsArray, int nCurrSize) {
	int** copy = *betsArray;
	*betsArray = (int**)realloc(*betsArray, (nCurrSize + ALLOCBET) * sizeof(int*));
	if (!*betsArray) {
		*betsArray = copy;
		return 0;
	}
	memset(*betsArray + nCurrSize, 0, ALLOCBET * sizeof(int*));
	for (int i = nCurrSize; i < nCurrSize + ALLOCBET; i++) {
		(*betsArray)[i] = (int*)calloc(MAXBETS, sizeof(int));
		if (!(*betsArray)[i])
			return nCurrSize + i;
	}
	return nCurrSize + ALLOCBET;
}
int SetSex(Player* p, char c)
{
	if (c == 'm' || c == 'M')
		p->pSex = MALE;
	else if (c == 'f' || c == 'F')
		p->pSex = FEMALE;
	else
		return 0;
	return 1;
}
int SetDate(Player* p, int d, int m, int y)
{
	if (d < 1 || d > 31)
		return 0;
	if (m < 1 || m > 12)
		return 0;
	if (y <= 1970)
		return 0;

	p->pDate.day = d;
	p->pDate.year = y;

	tm _tmp;
	memset(&_tmp, 0, sizeof(tm));

	_tmp.tm_mday = d;
	_tmp.tm_mon = m - 1;
	_tmp.tm_year = y - 1900;
	mktime(&_tmp);

	switch (_tmp.tm_wday)
	{
	case 0:
		p->pDate.weekDay = sun;
		break;
	case 1:
		p->pDate.weekDay = mon;
		break;
	case 2:
		p->pDate.weekDay = tue;
		break;
	case 3:
		p->pDate.weekDay = wed;
		break;
	case 4:
		p->pDate.weekDay = thu;
		break;
	case 5:
		p->pDate.weekDay = fri;
		break;
	case 6:
		p->pDate.weekDay = sat;
		break;
	default: return 0;
	}

	switch (_tmp.tm_mon)
	{
	case 0:
		p->pDate.monthName = Jan;
		break;
	case 1:
		p->pDate.monthName = Feb;
		break;
	case 2:
		p->pDate.monthName = Mar;
		break;
	case 3:
		p->pDate.monthName = Apr;
		break;
	case 4:
		p->pDate.monthName = May;
		break;
	case 5:
		p->pDate.monthName = Jun;
		break;
	case 6:
		p->pDate.monthName = Jul;
		break;
	case 7:
		p->pDate.monthName = Aug;
		break;
	case 8:
		p->pDate.monthName = Sep;
		break;
	case 9:
		p->pDate.monthName = Nov;
		break;
	case 10:
		p->pDate.monthName = Oct;
		break;
	case 11:
		p->pDate.monthName = Dec;
		break;
	default: return 0;
	}
	return 1;
}
//*** ------- ***///

int ReadData(Player*** pAllDraws, const char* sFileName)
{
	FILE* fin = fopen(sFileName, "r");
	if (!fin) {
		cout << "Couldn't open file\n";
		return 0;
	}
	int i = 0;
	int nCurrSize = 0;
	Player** pDrawsCopy = *pAllDraws;

	char c;
	if (!fscanf(fin, "%c", &c)) return 0;
	if (c != '*') return 0;


	while (!feof(fin)) {
		// Sprawdzenie, czy trzeba realokowaæ pamiêæ
		if (i == nCurrSize) {
			nCurrSize = AllocAddMem(&pDrawsCopy, nCurrSize);
			if (i == nCurrSize) {
				printf("Realloc error!\n");
				return 0;
			}
		}
		Player** players = pDrawsCopy + i;

		*players = (Player*)calloc(1, sizeof(Player));
		if (!*players) break;


		int d, m, y;
		if (!fscanf(fin, "%s %s %c %s %s %d:%d %d/%d/%d %s",
			&(*players)->pLastName,
			&(*players)->pFirstName,
			&c,
			&(*players)->bankInfo.Swift,
			&(*players)->bankInfo.IBan,
			&(*players)->hour,
			&(*players)->minute,
			&d,
			&m,
			&y,
			&(*players)->pesel
		)) return i;
		if (!SetSex(*players, c)) {
			cout << "Error: Can't set sex\n";
			return i;
		}
		if (!SetDate(*players, d, m, y)) {
			cout << "Error: Can't set date\n";
			return i;
		}

		int bets = 0;
		int currBetsSize = 0;

		while ((c = fgetc(fin)) != '*' && !feof(fin)) {
			ungetc(c, fin);
			if (bets == currBetsSize) {
				currBetsSize = AllocAddBetsMem(&(*players)->betsArray, currBetsSize);
				if (bets == currBetsSize) break;
			}

			int** betsRow = (*players)->betsArray + bets;
			int* betsCol = *betsRow;

			for (int j = 0; j < MAXBETS; j++, betsCol++) {
				if (!fscanf(fin, " %d ", betsCol)) {
					cout << "Error: Bet not loaded";
					return i;
				}
			}

			bets++;
		}
		(*players)->betsSize = bets;
		i++;
	}

	*pAllDraws = pDrawsCopy;
	fclose(fin);
	return i;
}

void FreeMem(Player*** pTab, int nDrawsNo) {
	Player** players = *pTab;

	for (int i = 0; i < nDrawsNo; i++, players++) {
		int size = (*players)->betsSize;
		for (int j = 0; j < (size + size % ALLOCBET); j++)
		{
			free((*players)->betsArray[j]);
		}
		free((*players)->betsArray);
		free((*players));
	}

	free(*pTab);
	*pTab = NULL;
}