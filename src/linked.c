/*
 * linkedList.c
 *
 *  Created on: 14 de mar de 2016
 *      Author: Thiago
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked.h"
#include "benchmark.h"
#include "sequential.h"

Node **ref;

int loadLinkedList(Header *head, char fileName[]) {

	system("cls");
	printf("\n Carregando %s para lista Encadeada. . .\n", fileName);

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

	while (fgets(string, 50, fp)) {

		splitRGl(head, string);

//		printf("%s\n", string);
	}
	endBenchmark(bm);

	fclose(fp);
	return 1;
}

void writeLinkedList(Header *head) {

	if (head->nodeCount > 0) {

		FILE *f = fopen("linkedList.txt", "w");
		if (f == NULL) {
			printf("Error opening file!\n");
			exit(1);
		}

		system("cls");
		printf("\n Escrevendo arquivo . . .\n");

		int i = 0;

		startBenchmark();

//		Node *aux;
//		aux = head->head;
//		for (i = 0; i < head->nodeCount; i++) {
//
//			fprintf(f, "%s,%d \n", aux->rg.nome, aux->rg.nr);
//			aux = aux->next;
//		}

		for (i = 0; i < head->nodeCount; i++) {
			fprintf(f, "%s,%d \n", ref[i]->rg.nome, ref[i]->rg.nr);
		}

		endBenchmark();

		fclose(f);

	} else {
		printf("\nLista vazia.\n");
	}

}

void splitRGl(Header *head, char string[100]) {

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

	insertNodeAtTheEnd(head, rg, 0);
}

void insertAtN(Header *head, RG value, int k) {

	startBenchmark();
	BM bm = { 0 }, aux;

	if (k == 0) {
		bm.nC += 1;
		aux = insertNodeAtStart(head, value, 0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else if (k == head->nodeCount) {
		bm.nC += 1;
		insertNodeAtTheEnd(head, value, 0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else {
		bm.nC += 2;
		int i;
		Node *aux, *newNode = (Node *) malloc(sizeof(Node));
		aux = head->head;

		for (i = 0; i < k; i++) {
			aux = aux->next;
			bm.nA += 1;
		}

		newNode->rg = value;
		newNode->next = aux;
		newNode->prev = aux->prev;
		newNode->prev->next = newNode;
		aux->prev = newNode;
		head->nodeCount++;
		bm.nA += 7;
	}

	endBenchmark(bm);
}

void wipeList(Header *head) {
	if (head->nodeCount > 0) {
		Node *aux;

		aux = head->head;
		while (aux->next != NULL) {
			aux = aux->next;
			free(aux->prev);
		}
		free(aux);
		head->head = NULL;
		head->tail = NULL;
		head->nodeCount = 0;
	}
}

BM insertNodeAtStart(Header *head, RG value, int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();

	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->rg = value;
	newNode->prev = NULL;
	if (head->head == NULL) {
		/*
		 * if the head is NULL means that the list was empty, then we should also set
		 * this new element as tail of the list.
		 */
		newNode->next = NULL;
		head->tail = newNode;
		head->head = newNode;
	} else {
		newNode->next = head->head;
		head->head->prev = newNode;
		head->head = newNode;
	}
	head->nodeCount++;

	bm.nA += 6;
	bm.nC += 1;

	if (bench)
		endBenchmark(bm);

	return bm;
}

BM insertNodeAtTheEnd(Header *head, RG value, int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();

	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->rg = value;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (head->head == NULL) {
		/*
		 * if the head is NULL means that the list was empty, then we should also set
		 * this new element as tail of the list.
		 */
		head->head = newNode;
		head->tail = newNode;
		newNode->prev = NULL;
	} else {
		head->tail->next = newNode;
		newNode->prev = head->tail;
		head->tail = newNode;
	}
	head->nodeCount++;

	bm.nA += 6;
	bm.nC += 1;

	if (bench)
		endBenchmark(bm);

	return bm;
}

void printList(Header *head) {

	startBenchmark();

	if (head->nodeCount > 0) {
		int i = 0;

		for (i = 0; i < head->nodeCount; i++) {
			printf("\nPOS: %d\n", i);
			printf("NOME: %s\n", ref[i]->rg.nome);
			printf("NR: %d\n", ref[i]->rg.nr);
		}
	} else {
		printf("\nLista vazia.\n");
	}

	endBenchmark();
}

BM deleteFirstNode(Header *head, int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();

	if (head->nodeCount > 1) {
		bm.nC += 1;
		printf("\nRemovendo node com valor: \n NOME:%s \n NR: %d .\n",
				head->tail->rg.nome, head->tail->rg.nr);
		system("PAUSE");

		Node *aux;
		aux = head->head;

		head->head = aux->next;
		head->head->prev = NULL;
		head->nodeCount--;

		free(aux);
		bm.nA += 3;
	} else if (head->nodeCount == 1) {
		bm.nC += 2;
		printf("\nRemovendo node com valor: \n NOME:%s \n NR: %d .\n",
				head->tail->rg.nome, head->tail->rg.nr);
		system("PAUSE");

		wipeList(head);
	}

	if (bench)
		endBenchmark(bm);

	return bm;
}

void deleteNodeAtN(Header *head, int k) {
	BM bm = { 0 }, aux;
	startBenchmark();

	if (head->nodeCount == 0) {
		bm.nC += 1;
		printf("\nLista vazia.\n");
		system("PAUSE");
	} else if (head->nodeCount == 1) {
		bm.nC += 2;
		wipeList(head);
	} else if (k == 0) {
		bm.nC += 3;
		aux = deleteFirstNode(head, 0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else if (k == head->nodeCount - 1) {
		bm.nC += 4;
		aux = deleteLastNode(head, 0);
		bm.nC += aux.nC;
		bm.nA += aux.nA;
	} else {
		int i;
		Node *aux;
		aux = head->head;

		for (i = 0; i < k; i++) {
			aux = aux->next;
			bm.nA += 1;
		}

		aux->next->prev = aux->prev;
		aux->prev->next = aux->next;
		head->nodeCount--;

		printf("\nRemovendo node com valor: \n NOME:%s \n NR: %d .\n",
				head->tail->rg.nome, head->tail->rg.nr);
		system("PAUSE");

		bm.nA += 3;

		free(aux);
	}

	endBenchmark(bm);
}

BM deleteLastNode(Header *head, int bench) {
	BM bm = { 0 };
	if (bench)
		startBenchmark();

	if (head->nodeCount > 1) {

		bm.nC += 1;

		printf("\nRemovendo node com valor: \n NOME:%s \n NR: %d .\n",
				head->tail->rg.nome, head->tail->rg.nr);
		system("PAUSE");

		Node *aux;
		aux = head->tail;

		head->tail = aux->prev;
		head->tail->next = NULL;
		head->nodeCount--;

		free(aux);
		bm.nA += 3;
	} else if (head->nodeCount == 1) {

		bm.nC += 2;

		printf("\nRemovendo node com valor: \n NOME:%s \n NR: %d .\n",
				head->tail->rg.nome, head->tail->rg.nr);
		system("PAUSE");

		wipeList(head);
	}

	if (bench)
		endBenchmark(bm);

	return bm;
}

void deleteNodeByValue(Header *head) {
	BM bm = { 0 };

	startBenchmark();

	int flag = 0, i, rg;
	Node *aux;
	aux = head->head;
	bm.nA += 1;

	printf("\n Digite o numero do documento a remover.\n");
	scanf("%d", &rg);

	for (i = 0; i < head->nodeCount && flag == 0; i++) {
		/*
		 * Checks if the node is the one we're searching for.
		 */
		if (aux->rg.nr == rg) {
			/*
			 * If the it's the node, we check if he's the first one.
			 */
			bm.nC += 1;
			printf("O valor %d foi encontrado no node %d. \n", rg, i);

			if (aux->prev == NULL) {
				bm.nC += 1;
				/*
				 * If he's the first node we have to redirect the header to the next one.
				 * In the case of this node being the only one, the value of his next should be NULL,
				 * and we shouldn't have any problem as long as we set the head->tail to NULL as well.
				 */
				head->head = aux->next;
				head->head->prev = NULL;
				if (head->nodeCount == 1) {
					head->tail = NULL;
					bm.nA += 1;
					bm.nC += 1;
				}
				free(aux);
				bm.nA += 2;
				head->nodeCount--;
				flag = 1;
			} else if (aux->next == NULL) {
				bm.nC += 2;
				/*
				 * If he's the last one we point the head->tail to his previous and NULL the next of the new tail.
				 */
				aux->prev->next = NULL;
				head->tail = aux->prev;
				free(aux);
				bm.nA += 2;
				head->nodeCount--;
				flag = 1;
			} else {
				bm.nC += 2;
				/*
				 * If the NODE is in the middle of the list we just point the NODE-1 to NODE+1,
				 * and the NODE+1 to NODE-1.
				 */
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;
				free(aux);
				head->nodeCount--;
				flag = 1;

				bm.nA += 2;
			}
			break;
		}
		aux = aux->next;
		bm.nA += 1;
	}

	if (flag == 0) {
		printf("\nNode com valor %d nao pode ser encontrado. \n", rg);
	}

	endBenchmark(bm);
}

RG getValue() {
	RG value;

	fflush(stdin);
	printf("\n Digite o nome do portador do documento.\n");
	fgets(value.nome, 50, stdin);
	value.nome[strlen(value.nome) - 1] = '\0';
	fflush(stdin);

	printf("\n Digite o numero do documento.\n");
	scanf("%d", &value.nr);
	fflush(stdin);

	return value;
}

int getPosIns(Header *head) {
	int pos;

	do {
		system("cls");
		printf("\n Digite a posicao desejada.\n");
		printf("Valores inteiros de 0 a %d apenas.\n", head->nodeCount);
		scanf("%d", &pos);
	} while (!(pos >= 0 && pos <= head->nodeCount));
	return pos;
}

int getPosDel(Header *head) {
	int pos;

	if (head->nodeCount != 0) {
		do {
			system("cls");
			printf("\n Digite a posicao desejada.\n");
			printf("Valores inteiros de 0 a %d apenas.\n", head->nodeCount - 1);
			scanf("%d", &pos);
		} while (!(pos >= 0 && pos <= head->nodeCount - 1));
	}

	return pos;
}

void startRef(int size) {
	free(ref);
	ref = (Node**) malloc(size * sizeof(Node*));
}

void reference(Header *head) {
	printf("Ref...");
	startBenchmark();
	BM bm = { 0 };
	int i;
	Node *aux;
	aux = head->head;

	startRef(head->nodeCount);

	for (i = 0; i < head->nodeCount; i++) {
		ref[i] = aux;

		aux = aux->next;
	}
	endBenchmark(bm);
}

void linkedInserctionSort(Header *head) {
	startBenchmark();
	BM bm = { 0 };

	int i, j;
	Node *temp;

	for (i = 1; i < head->nodeCount; i++) {
		j = i - 1;
		bm.nA += 1;
		while (ref[j + 1]->rg.nr < ref[j]->rg.nr) {
			temp = ref[j];
			ref[j] = ref[j + 1];
			ref[j + 1] = temp;
			if (j > 0) {
				j--;
			} else {
				break;
			}
			bm.nC += 2;
			bm.nA += 3;
		}
	}
	endBenchmark(bm);
}

void linkedSelectionSort(Header *head) {
	startBenchmark();
	BM bm = { 0 };

	int i, j, menorIdx;
	Node *temp;

	for (i = 0; i < head->nodeCount - 1; i++) {
		menorIdx = i;
		bm.nA += 2;
		bm.nC += 1;
		for (j = i + 1; j < head->nodeCount; j++) {
			bm.nA += 2;
			bm.nC += 1;
			if (ref[j]->rg.nr < ref[menorIdx]->rg.nr) {
				menorIdx = j;
				bm.nA += 1;
			}
		}
		temp = ref[menorIdx];
		ref[menorIdx] = ref[i];
		ref[i] = temp;
		bm.nA += 3;
	}
	endBenchmark(bm);
}

void linkedBubbleSort(Header *head) {
	startBenchmark();
	BM bm = { 0 };

	int i, j;
	Node *aux;

	for (i = head->nodeCount - 1; i >= 0; i--) {
		bm.nA += 1;
		bm.nC += 1;
		for (j = 0; j < i; j++) {
			bm.nA += 1;
			bm.nC += 1;
			if (ref[j]->rg.nr > ref[j + 1]->rg.nr) {
				aux = ref[j];
				ref[j] = ref[j + 1];
				ref[j + 1] = aux;
				bm.nA += 3;
			}
			bm.nC += 1;
		}
	}
	endBenchmark(bm);
}

void linkedShellSort(Header *head) {

	startBenchmark();
	BM bm = { 0 };

	int i, j, k;
	Node *tmp;

	for (i = head->nodeCount / 2; i > 0; i = i / 2) {
		bm.nA += 1;
		bm.nC += 1;
		for (j = i; j < head->nodeCount; j++) {
			bm.nA += 1;
			bm.nC += 1;
			for (k = j - i; k >= 0; k = k - i) {
				bm.nA += 1;
				bm.nC += 2;
				if (ref[k + i]->rg.nr >= ref[k]->rg.nr)
					break;
				else {
					tmp = ref[k];
					ref[k] = ref[k + i];
					ref[k + i] = tmp;
					bm.nA += 3.;
				}
			}
		}
	}

	endBenchmark(bm);
}

void linkedCallQuickSort(Header *head) {
	startBenchmark();
	BM bm = { 0 };
	bm = linkedQuickSort(0, head->nodeCount - 1, bm);
	endBenchmark(bm);
}

BM linkedQuickSort(int left, int right, BM bm) {

	int i = left, j = right;
	Node *tmp;
	Node *pivot = ref[(left + right) / 2];
	bm.nA += 1;

	while (i <= j) {
		bm.nC += 1;
		while (ref[i]->rg.nr < pivot->rg.nr) {
			i++;
			bm.nC += 1;
		}
		while (ref[j]->rg.nr > pivot->rg.nr) {
			j--;
			bm.nC += 1;
		}
		if (i <= j) {
			tmp = ref[i];
			ref[i] = ref[j];
			ref[j] = tmp;
			i++;
			j--;
			bm.nA += 3;
		}
		bm.nC += 1;
	};

	if (left < j) {
		bm = linkedQuickSort(left, j, bm);
	}
	if (i < right) {
		bm = linkedQuickSort(i, right, bm);
	}

	return bm;
}

BM linkedMerge(Node **a, int n, int m, BM bm) {
	int i, j, k;
	Node **x = malloc(n * sizeof(Node*));
	for (i = 0, j = m, k = 0; k < n; k++) {
		if (j == n) {
			x[k] = a[i++];
			bm.nC += 1;
			bm.nA += 1;
		} else if (i == m) {
			x[k] = a[j++];
			bm.nC += 2;
			bm.nA += 1;
		} else if (a[j]->rg.nr < a[i]->rg.nr) {
			x[k] = a[j++];
			bm.nC += 3;
			bm.nA += 1;
		} else {
			x[k] = a[i++];
			bm.nC += 3;
			bm.nA += 1;
		}
	}
	for (i = 0; i < n; i++) {
		a[i] = x[i];
		bm.nA += 1;
	}

	free(x);

	return bm;
}

BM linkedMergeSort(Node **a, int n, BM bm) {

	if (n < 2)
		return bm;
	int m = n / 2;
	bm = linkedMergeSort(a, m, bm);
	bm = linkedMergeSort(a + m, n - m, bm);
	bm = linkedMerge(a, n, m, bm);

	return bm;
}

void linkedCallMergeSort(int size) {
	startBenchmark();
	BM bm = { 0 };
	bm = linkedMergeSort(ref, size, bm);
	endBenchmark(bm);
}

void linkedCallBynarySearch(Header *head) {

	int rg = 0, idx;

	fflush(stdin);
	printf("\n Digite o numero do documento.\n");
	scanf("%d", &rg);

	startBenchmark();
	BM bm = { 0 };

	idx = linkedBynarySearch(rg, 0, head->nodeCount, bm);

	if (idx == -1) {
		printf("\nO valor %d nao pode ser encontrado. \n", rg);
	} else {
		printf("\nO valor %d pode ser encontrado na posicao %d. \n", rg, idx);
		printf("\nPOS: %d\n", idx);
		printf("NOME: %s\n", ref[idx]->rg.nome);
		printf("NR: %d\n", ref[idx]->rg.nr);
	}
}

int linkedBynarySearch(int value, int start, int finish, BM bm) {
	bm.nC += 1;
	if (start > finish) {
		return -1;
	}

	int m = start + (finish - start) / 2;
	bm.nA += 1;

	if (ref[m]->rg.nr < value) {
		bm.nC += 1;
		return linkedBynarySearch(value, m + 1, finish, bm);
	} else if (ref[m]->rg.nr > value) {
		bm.nC += 1;
		return linkedBynarySearch(value, start, m - 1, bm);
	}

	endBenchmark(bm);
	return m;
}

void searchNodeByValue(Header *head) {
	BM bm = { 0 };

	startBenchmark();

	int flag = 0, i, rg;

	fflush(stdin);
	printf("\n Digite o numero do documento.\n");
	scanf("%d", &rg);


	for (i = 0; i < head->nodeCount && flag == 0; i++) {
		bm.nC += 1;
		if (ref[i]->rg.nr == rg) {
			printf("O valor %d foi encontrado no node %d. \n", rg, i);
			flag = 1;
		}
	}

	if (flag == 0) {
		printf("\nNode com valor %d nao pode ser encontrado. \n", rg);
	}

	endBenchmark(bm);
}
