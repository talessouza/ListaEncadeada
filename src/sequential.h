/*
 * sequential.h
 *
 *  Created on: 15 de mar de 2016
 *      Author: Thiago
 */

#ifndef SEQUENTIAL_H_
#define SEQUENTIAL_H_

#include "benchmark.h"

//struct rg {
//	char nome[50];
//	int nr;
//}typedef RG;

void reallocSeq();
void startSeq();
void reallocBig(int fileLines);

BM insertSeqAtTheEnd(RG rg, int bench);
BM insertSeqAtStart(RG rg, int bench);
void insertSeqAtN(RG rg, int n);
BM deleteFirstSeq(int bench);
BM deleteLastSeq(int bench);
BM deleteSeqAtN(int n, int bench);
void printSeq();
int getPosSeqDel();

void writeSequentialList();
void splitRG(char string[100]);
int loadSequentialList(char fileName[], int fileLines);
BM insertSeqAtTheEndNoRealloc(RG rg, int bench);

void inserctionSort();
void selectionSort();
void bubbleSort();
void shellSort();
void callQuickSort();
BM quickSort(int left, int right, BM bm);
BM seqMergeSort(RG *a, int n, BM bm);
BM seqMerge(RG *a, int n, int m, BM bm);
void callMergeSort();

void callBynarySearch();
int bynarySearch(int value, int start, int finish, BM bm);

#endif /* SEQUENTIAL_H_ */
