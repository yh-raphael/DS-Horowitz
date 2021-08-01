#include <stdio.h>
#include <stdlib.h>
#include "ListBaseStack.h"

void StackInit(Stack* pstack)
{
	pstack->head = NULL;
}

int SIsEmpty(Stack* pstack)
{
	if (pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data1, Data data2)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data1 = data1;
	newNode->data2 = data2;
	newNode->next = pstack->head;

	pstack->head = newNode;
}

void SPop(Stack* pstack, Data* data1, Data* data2)
{
//	Data rdata;
	Node* rnode;

	if (SIsEmpty(pstack)) {
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	*data1 = pstack->head->data1;
	*data2 = pstack->head->data2;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);
//	return rdata;
}
/*
Data SPeek(Stack* pstack)
{
	if (SIsEmpty(pstack)) {
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	return pstack->head->data;
}
*/