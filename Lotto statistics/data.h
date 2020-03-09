#pragma once
#include "defs.h"

int ReadData(Player*** pAllDraws, const char* sfileName); // zwraca ilosc przeczytanych danych;
//	int AllocAddMem( Player*** pTab, int nCurrSize ); // realokacja dla graczy
//	int AllocAddBetsMem( int*** betsArray, int nCurrSize );
void FreeMem(Player*** pTab, int nDrawsNo);
//	int SetSex( Player* p, char c );  // 0, nie powiodlo sie
//	int SetDate( Player* p, int d, int m, int y ); // 0 nie powiodlo sie