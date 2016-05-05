/*
 * sequential.c
 *
 *  Created on: 14 de mar de 2016
 *      Author: Thiago
 */

#include <stdlib.h>
#include <stdio.h>
#include "linked.h"
#include "sequential.h"

int size = 0;
RG *seq;

void startSeq() {
	free(seq);
	seq = (RG*) malloc(size * sizeof(RG));
}

void reallocSeq() {
	seq = (RG *) realloc(seq, size * sizeof(RG));
}

void reallocBig(int fileLines) {
	fileLines+=size;

	seq = (RG *) realloc(seq, fileLines * sizeof(RG));
}

int loadSequentialList(char fileName[], int fileLines) {

	reallocBig(fileLines);

	system("cls");
	printf("\n Carregando %s para lista Sequencial. . .\n", fileName);

	BM bm = { 0 };

	FILE *fp;
	fp = fopen(fileName, "r");

	/* opening file for reading */
	if (fp == NULL) {
		perror("Error opening file");
		return (-1);
	}

	char string[50];

	startBenchmark();

//	unsigned long int a = 0;

	while (fgets(string, 50, fp)) {

//		printf("\n lendo %lu", a);
		splitRG(string);
//		a++;
//		printf("%s\n", string);
	}
	endBenchmark(bm);

	fclose(fp);

	system("pause");
	printf("\ntamanho lista %d", size);

	return 1;
}

void splitRG(char string[100]) {

	int i, j = 0, flag = 0;
	char strRg[50];

	RG rg;

	for (i = 0; i < 50 && string[i] != '\0'; i++) {
		if (string[i] != ',') {
			if (flag == 0) {
				rg.nome[j] = string[i];
			} else {
				strRg[j] = string[i];
			}
			j++;
		} else {
			rg.nome[j] = '\0';
			j = 0;
			flag = 1;
		}
	}

	strRg[j] = '\0';

	sscanf(strRg, "%d", &rg.nr);

	insertSeqAtTheEndNoRealloc(rg, 0);
}

void writeSequentialList() {
	if (size > 0) {

		FILE *f = fopen("sequentialList.txt", "w");
		if (f == NULL) {
			printf("Error opening file!\n");
			exit(1);
		}

		system("cls");
		printf("\n Escrevendo arquivo . . .\n");

		int i = 0;

		startBenchmark();

		for (i = 0; i < size; i++) {
			fprintf(f, "%s,%d \n", seq[i].nome, seq[i].nr);
		}

		endBenchmark();

		fclose(f);

	} else {
		printf("\nLista vazia.\n");
	}
}

void printSeq() {
	int i;
	for (i = 0; i < size; i++) {
		printf("\nPOS: %d\n", i);
		printf("NOME: %s\n", seq[i].nome);
		printf("NR: %d\n", seq[i].nr);
	}
}

BM insertSeqAtTheEndNoRealloc(RG rg, int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();

	size++;
	if (size == 1) {
		seq[0] = rg;
	} else {
		seq[size - 1] = rg;
	}

	bm.nA += 1;
	bm.nC += 1;

	if (bench)
		endBenchmark(bm);

	return bm;
}

BM insertSeqAtTheEnd(RG rg, int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();

	size++;
	if (size == 1) {
		startSeq();
		seq[0] = rg;
	} else {
		reallocSeq();
		seq[size - 1] = rg;
	}

	bm.nA += 1;
	bm.nC += 1;

	if (bench)
		endBenchmark(bm);

	return bm;
}

BM insertSeqAtStart(RG rg, int bench) {
	BM bm = { 0 };

	if (bench)
		startBenchmark();

	size++;
	if (size == 1) {
		startSeq();
		seq[0] = rg;
	} else {
		int i;
		reallocSeq();

		for (i = size - 1; i > 0; i--) {
			seq[i] = seq[i - 1];
			bm.nA += 1;
		}
		seq[0] = rg;
	}

	bm.nA += 1;
	bm.nC += 1;

	if (bench)
		endBenchmark(bm);

	return bm;
}

void insertSeqAtN(RG rg, int n) {
	BM bm = { 0 }, aux;
	startBenchmark();

	if (n == 0) {
		bm.nC += 1;
		aux = insertSeqAtStart(rg, 0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else if (n == size) {
		bm.nC += 2;
		aux = insertSeqAtTheEnd(rg, 0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else {
		bm.nC += 2;
		int i;
		size++;
		reallocSeq();

		for (i = size - 1; i > n; i--) {
			seq[i] = seq[i - 1];
			bm.nA += 1;
		}
		seq[n] = rg;
		bm.nA += 1;
	}
	endBenchmark(bm);
}

BM deleteFirstSeq(int bench) {
	BM bm = { 0 };

	if (bench)
		startBenchmark();

	int i;
	printf("\nRemovendo entrada com valor: \n NOME:%s \n NR: %d .\n",
			seq[0].nome, seq[0].nr);
	for (i = 0; i < size - 1; i++) {
		seq[i] = seq[i + 1];
		bm.nA += 1;
	}
	size--;
	reallocSeq();

	if (bench)
		endBenchmark(bm);

	return bm;
}

BM deleteLastSeq(int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();
	printf("\nRemovendo entrada com valor: \n NOME:%s \n NR: %d .\n",
			seq[size - 1].nome, seq[size - 1].nr);
	size--;
	reallocSeq();

	if (bench)
		endBenchmark(bm);

	return bm;
}

BM deleteSeqAtN(int n, int bench) {
	BM bm = { 0 }, aux;
	if (bench)
		startBenchmark();

	if (n == 0) {
		bm.nC += 1;
		aux = deleteFirstSeq(0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else if (n == size - 1) {
		bm.nC += 2;
		aux = deleteLastSeq(0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else {
		bm.nC += 2;
		int i;
		printf("\nRemovendo entrada com valor: \n NOME:%s \n NR: %d .\n",
				seq[n].nome, seq[n].nr);
		for (i = n; i < size - 1; i++) {
			seq[i] = seq[i + 1];
			bm.nA += 1;
		}
		size--;
		reallocSeq();
	}

	if (bench)
		endBenchmark(bm);

	return bm;
}

void deleteSeqByValue() {
	BM bm = { 0 }, aux;
	startBenchmark();

	int rg, i, flag = 0;

	printf("\n Digite o numero do documento a remover.\n");
	scanf("%d", &rg);

	for (i = 0; i < size && flag == 0; i++) {
		if (seq[i].nr == rg) {
			aux = deleteSeqAtN(i, 0);
			bm.nC += aux.nC;
			bm.nA += aux.nA;
			flag = 1;
		}
		bm.nC += 1;
	}

	if (flag == 0) {
		printf("\nO valor %d nao pode ser encontrado. \n", rg);
	}

	endBenchmark(bm);
}

int getPosSeqDel() {
	int pos;

	if (size != 0) {
		do {
			system("cls");
			printf("\n Digite a posicao desejada.\n");
			printf("Valores inteiros de 0 a %d apenas.\n", size - 1);
			scanf("%d", &pos);
		} while (!(pos >= 0 && pos <= size - 1));
	}

	return pos;
}

int getPosSeqIns() {
	int pos;

	do {
		system("cls");
		printf("\n Digite a posicao desejada.\n");
		printf("Valores inteiros de 0 a %d apenas.\n", size);
		scanf("%d", &pos);
	} while (!(pos >= 0 && pos <= size));
	return pos;
}
