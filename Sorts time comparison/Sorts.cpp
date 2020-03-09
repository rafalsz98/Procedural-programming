#include "Sorts.h"
#include "Tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

void SelectionSort(int* tab, int nSize) {
	for (int i = 0; i < nSize - 1; i++) {
		int k = i;
		int x = tab[i];

		for (int j = i + 1; j < nSize; j++) {
			if (tab[j] < x) {
				k = j;
				x = tab[k];
			}
		}
		tab[k] = tab[i];
		tab[i] = x;
	}
}

void InsertionSort(int* tab, int nSize) {
	for (int i = 1; i < nSize; i++) {
		int key = tab[i];
		int j = i - 1;

		while (j >= 0 && tab[j] > key)
			tab[j + 1] = tab[j--];
		tab[j + 1] = key;
	}
}

void HalfInsertionSort(int* tab, int nSize) {
	for (int i = 1; i < nSize; i++) {
		int val = tab[i];
		int begin = 0;
		int end = i - 1;
		while (begin <= end) {
			int mid = (begin + end) / 2;
			if (val < tab[mid])
				end = mid - 1;
			else
				begin = mid + 1;
		}

		for (int j = i - 1; j >= begin; j--) {
			tab[j + 1] = tab[j];
		}

		tab[begin] = val;
	}
}

void BubbleSort(int* tab, int nSize) {
	for (int i = 0; i < nSize - 1; i++) {
		for (int j = nSize - 1; j > i; j--) {
			if (tab[j] < tab[j - 1]) {
				int temp = tab[j];
				tab[j] = tab[j - 1];
				tab[j - 1] = temp;
			}
		}
	}
}

void MixedBubbleSort(int* tab, int nSize) {
	int start = 1; // Lewy indeks
	int end = nSize - 1; // Prawy indeks
	int k = end;
	do {
		for (int j = end; j >= start; j--) {
			if (tab[j - 1] > tab[j]) {
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
				k = j;
			}
		}
		// Element na indeksie start jest ju¿ na swoim miejscu
		start = k + 1;
		for (int j = start; j <= end; j++) {
			if (tab[j - 1] > tab[j]) {
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
				k = j;
			}
		}
		// Element na indeksie end jest ju¿ na swoim miejscu
		end = k - 1;
	} while (start < end);
}

void Update(int* tab, int L, int R) {
	if (L == R) return;
	int i = L;
	int j = 2 * i + 1;
	int x = tab[i];

	while (j <= R) {
		if (j < R) {
			if (tab[j] < tab[j + 1])
				j++;
		}
		if (x > tab[j])
			break;
		tab[i] = tab[j];
		i = j;
		j = 2 * j + 1;
	}
	tab[i] = x;
}

void HeapSort(int* tab, int nSize) {
	// Budujemy kopiec od do³u
	for (int i = nSize / 2; i >= 0; i--) {
		Update(tab, 0, nSize - 1);
	}


	// Wyrzucamy pierwszy element na koniec tablicy i naprawiamy warunek stosu
	for (int i = nSize - 1; i > 0; i--) {
		int high = tab[0];
		tab[0] = tab[i];
		tab[i] = high;
		Update(tab, 0, i - 1);
	}

}

void QuickSort(int* tab, int low, int high) {
	int i = low;
	int j = high;
	int x = tab[(low + high) / 2];

	do {
		while (tab[i] < x) i++;
		while (tab[j] > x) j--;

		if (i <= j) {
			int temp = tab[i];
			tab[i++] = tab[j];
			tab[j--] = temp;
		}
	} while (i <= j);

	if (low < j) QuickSort(tab, low, j);
	if (i > high) QuickSort(tab, i, high);
}

void Merge1(int* tab, int low, int mid, int high, int* L, int* R) {
	int n1 = mid - low + 1; // Rozmiar 1 tablicy
	int n2 = high - mid; // Rozmiar 2 tablicy

	// Przekopiowanie elementów do utworzonych tablic
	memcpy(L, &tab[low], sizeof(int) * n1);
	memcpy(R, &tab[mid + 1], sizeof(int) * n2);

	int i = 0; // Indeks dla tablicy lewej
	int j = 0; // Indeks dla tablicy prawej
	int k = low; // Indeks dla tablicy g³ównej

	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			tab[k++] = L[i++];
		else
			tab[k++] = R[j++];
	}

	// Wpisanie pozosta³ych elementów do tablicy g³ównej
	while (i < n1)
		tab[k++] = L[i++];

	//while ( j < n2 )
		//tab[k++] = R[j++];

}

void MergeSort1(int* tab, int low, int high, int* L, int* P) {
	// Dopóki indeks lewy jest mniejszy od indeksu prawego rekurencja siê wykonuje
	if (low < high) {
		int mid = low + (high - low) / 2;

		MergeSort1(tab, low, mid, L, P);
		MergeSort1(tab, mid + 1, high, L, P);

		Merge1(tab, low, mid, high, L, P);
	}
}

void Merge2(int* tab, int low, int mid, int high, int* arr) {
	// Rozmiar nowej tablicy
	int N = high - low + 1;

	// Kopiowanie elementów do tej tablicy
	memcpy(arr, &tab[low], sizeof(int) * N);

	int i = 0; // Indeks dla lewej po³ówki tablicy
	int j = (N + 1) / 2; // Indeks dla prawej po³ówki tablicy
	int k = low; // Indeks tablicy g³ównej

	while (i < (N + 1) / 2 && j < N) {
		if (arr[i] <= arr[j])
			tab[k++] = arr[i++];
		else
			tab[k++] = arr[j++];
	}
	// Wpisanie pozosta³ych elementów do tablicy g³ównej
	while (i < (N + 1) / 2)
		tab[k++] = arr[i++];

	//while ( j < N )
	//	tab[k++] = arr[j++];
}

void MergeSort2(int* tab, int low, int high, int* arr) {
	if (low < high) {
		int mid = low + (high - low) / 2;

		MergeSort2(tab, low, mid, arr);
		MergeSort2(tab, mid + 1, high, arr);

		Merge2(tab, low, mid, high, arr);
	}
}
