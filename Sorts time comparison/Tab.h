#ifndef TAB_H

int* createTab(int nSize);                      // malloc + memset + if
void freeTab(int* pTab);
void initTab(int* pTab, int nSize, int nVal);   // zainicjowanie jak�� warto�ci�
void randInit(int* pTab, int nSize);            // %nSize
void copyTab(int* pTabTo, int* pTabFrom, int nSize);

#endif // !TAB_H
