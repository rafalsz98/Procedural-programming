#ifndef SORTS_H

void SelectionSort(int* tab, int nSize);
void InsertionSort(int* tab, int nSize);       // sortowanie do lewej
void HalfInsertionSort(int* tab, int nSize);
void BubbleSort(int* tab, int nSize);
void MixedBubbleSort(int* tab, int nSize);
void HeapSort(int* tab, int nSize); // bez rekurencji'
void QuickSort(int* tab, int low, int high);
void MergeSort1(int* tab, int low, int high, int* L, int* P); // na 2 tablicach
void MergeSort2(int* tab, int low, int high, int* M); // na 1 tablicy

#endif // !SORTS_H

