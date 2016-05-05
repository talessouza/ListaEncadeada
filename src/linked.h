#ifndef __LINKED_H
#define __LINKED_H

#include "benchmark.h"

struct rg {
	char nome[50];
	int nr;
}typedef RG;

struct node {
	RG rg;
	struct node *prev;
	struct node *next;
}typedef Node;

struct header {
	Node *head;
	Node *tail;
	int nodeCount;
}typedef Header;

void splitRGl(Header *head, char string[50]);
int loadLinkedList(Header *head, char fileName[]);

BM insertNodeAtTheEnd(Header *head, RG value, int bench);
BM insertNodeAtStart(Header *head, RG value, int bench);
void printList(Header *head);
void deleteNodeByValue(Header *head);
void insertAtN(Header *head, RG value, int k);
RG getValue();
int getPosIns(Header *head);
int getPosDel(Header *head);
void wipeList(Header *head);
BM deleteLastNode(Header *head, int bench);
BM deleteFirstNode(Header *head, int bench);
void deleteNodeAtN(Header *head, int k);
void writeLinkedList(Header *head);

#endif