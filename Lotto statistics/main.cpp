#include <iostream>
#include "defs.h"
#include "data.h"
#include "print.h"

using namespace std;


void HeapCheck();
void CalcStat(int* pNums50, Player** pPlayers, int nPlayersNo);
void Sort(Player** pPlayers, int nPlayersNo);

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: Lotto.exe <input file>\n");
		return -1;
	}

	Player** playersArray = NULL;
	int stats[LOTTOMAX] = {0};

	int m = ReadData(&playersArray, argv[1]);
	if (!m) {
		cout << "Error: Couldn't load players\n";
		return -1;
	}

	Sort(playersArray, m);
	CalcStat(stats, playersArray, m);
	PrintResults(stats, playersArray, m);


	FreeMem(&playersArray, m);

	cout << endl;
	HeapCheck();
	return 0;
}

void HeapCheck()
{
	int  heapstatus;
	char* buffer;

	// Allocate and deallocate some memory
	if ((buffer = (char*)malloc(100)) != NULL)
		free(buffer);

	// Check heap status
	heapstatus = _heapchk();
	switch (heapstatus)
	{
	case _HEAPOK:
		printf(" OK - heap is fine\n");
		break;
	case _HEAPEMPTY:
		printf(" OK - heap is empty\n");
		break;
	case _HEAPBADBEGIN:
		printf("ERROR - bad start of heap\n");
		break;
	case _HEAPBADNODE:
		printf("ERROR - bad node in heap\n");
		break;
	}
}

void CalcStat(int* pNums50, Player** pPlayer, int nPlayersNo)
{
	for (int i = 0; i < nPlayersNo; i++, pPlayer++) {
		int** betsRow = (*pPlayer)->betsArray;
		for (int j = 0; j < (*pPlayer)->betsSize; j++, betsRow++) {
			int* betsCol = *betsRow;
			for (int k = 0; k < MAXBETS; k++, betsCol++) {
				pNums50[*betsCol]++;
			}
		}
	}
}

void Sort(Player** pPlayers, int nPlayersNo) {
	for (int i = 0; i < nPlayersNo; i++) {
		int min = i;
		for (int j = i + 1; j < nPlayersNo; j++) {
			int _res = strcmp(pPlayers[min]->pLastName, pPlayers[j]->pLastName);
			if (_res > 0) {
				min = j;
			}
			else if (_res == 0) {
				if (strcmp(pPlayers[min]->pFirstName, pPlayers[j]->pFirstName) > 0) {
					min = j;
				}
			}
		}
		Player* tmp = pPlayers[i];
		pPlayers[i] = pPlayers[min];
		pPlayers[min] = tmp;
	}
}
