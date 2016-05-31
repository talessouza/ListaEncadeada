/*
 ============================================================================
 Name        : readFile.c
 Author      : asd
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked.h"
#include "sequential.h"

void listOptions(Header *head, int list);

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	Header head;

	head.head = NULL;
	head.tail = NULL;
	head.nodeCount = 0;

	int menu = 0, list = 0;

	do {

		do {
			system("cls");
			printf("\n Manipular qual lista.\n");
			printf("1 - Encadeada.\n");
			printf("2 - Sequencial.\n");

			scanf("%d", &list);

			system("cls");
		} while (list != 1 && list != 2);

		system("cls");
		printf("\n Digite o numero da opcao desejada.\n");
		printf("1 - Inserir elemento no final da lista.\n");
		printf("2 - Inserir elemento no inicio da lista.\n");
		printf("3 - Remover elemento a partir de um valor.\n");
		printf("4 - Imprimir a lista.\n");
		printf("5 - Inserir na posicao N.\n");
		printf("6 - Remover ultimo da lista.\n");
		printf("7 - Remover primeiro da lista.\n");
		printf("8 - Remover elemento na posicao N.\n");
		printf("9 - Carregar lista do arquivo.\n");
		printf("10 - Salvar lista atual em arquivo.\n");
		printf("11 - Inserction.\n");
		printf("12 - Selection.\n");
		printf("13 - Bubble.\n");
		printf("14 - Shell.\n");
		printf("15 - Quick.\n");

		printf("20 - Sair.\n");

		scanf("%d", &menu);

		system("cls");

		switch (menu) {
		case 1:
			if (list == 1) {
				insertNodeAtTheEnd(&head, getValue(), 1);
				reference(&head);
			} else {
				insertSeqAtTheEnd(getValue(), 1);
			}
			break;
		case 2:
			if (list == 1) {
				insertNodeAtStart(&head, getValue(), 1);
				reference(&head);
			} else {
				insertSeqAtStart(getValue(), 1);
			}
			break;
		case 3:
			if (list == 1) {
				deleteNodeByValue(&head);
				reference(&head);
			} else {
				deleteSeqByValue();
			}
			break;
		case 4:
			if (list == 1) {
				printList(&head);
			} else {
				printSeq();
			}
			break;
		case 5:
			if (list == 1) {
				insertAtN(&head, getValue(), getPosIns(&head));
				reference(&head);
			} else {
				insertSeqAtN(getValue(), getPosSeqIns());
			}
			break;
		case 6:
			if (list == 1) {
				deleteLastNode(&head, 1);
				reference(&head);
			} else {
				deleteLastSeq(1);
			}
			break;
		case 7:
			if (list == 1) {
				deleteFirstNode(&head, 1);
				reference(&head);
			} else {
				deleteFirstSeq(1);
			}
			break;
		case 8:
			if (list == 1) {
				deleteNodeAtN(&head, getPosDel(&head));
				reference(&head);
			} else {
				deleteSeqAtN(getPosSeqDel(), 1);
			}
			break;
		case 9:
			listOptions(&head, list);
			break;
		case 10:
			if (list == 1) {
				writeLinkedList(&head);
			} else {
				writeSequentialList();
			}
			break;
		case 11:
			if (list == 1) {
				linkedInserctionSort(&head);
			} else {
				inserctionSort();
			}
			break;
		case 12:
			if (list == 1) {
				linkedSelectionSort(&head);
			} else {
				selectionSort();
			}
			;
			break;
		case 13:
			if (list == 1) {
				linkedBubbleSort(&head);
			} else {
				bubbleSort();
			}
			break;
		case 14:
			if (list == 1) {
				linkedShellSort(&head);
			} else {
				shellSort();
			}
			break;
		case 15:
			if (list == 1) {
				linkedCallQuickSort(&head);
			} else {
				callQuickSort();
			}
			break;
		}

	} while (menu != 20);

	wipeList(&head);

	return EXIT_SUCCESS;
}

void listOptions(Header *head, int list) {

	int menu = 0, fileLines;
	char fileName[20] = { 0 };

	do {
		system("cls");
		printf("\n Qual lista deseja carregar.\n");
		printf("1 - NomeRG10.\n");
		printf("2 - NomeRG50.\n");
		printf("3 - NomeRG100.\n");
		printf("4 - NomeRG1K.\n");
		printf("5 - NomeRG10k.\n");
		printf("6 - NomeRG1M.\n");
		printf("7 - NomeRG100M.\n");

		scanf("%d", &menu);

		system("cls");

		switch (menu) {
		case 1:
			strncpy(fileName, "NomeRG10.txt", 20);
			fileLines = 10;
			break;
		case 2:
			strncpy(fileName, "NomeRG50.txt", 20);
			fileLines = 50;
			break;
		case 3:
			strncpy(fileName, "NomeRG100.txt", 20);
			fileLines = 100;
			break;
		case 4:
			strncpy(fileName, "NomeRG1k.txt", 20);
			fileLines = 1000;
			break;
		case 5:
			strncpy(fileName, "NomeRG10k.txt", 20);
			fileLines = 10000;
			break;
		case 6:
			strncpy(fileName, "NomeRG1M.txt", 20);
			fileLines = 1000000;
			break;
		case 7:
			strncpy(fileName, "NomeRG100M.txt", 20);
			fileLines = 11748444;
			break;
		}

	} while (menu < 1 && menu > 7);

	if (list == 1) {
		loadLinkedList(head, fileName);
		reference(head);
	} else {
		loadSequentialList(fileName, fileLines);
	}

}
