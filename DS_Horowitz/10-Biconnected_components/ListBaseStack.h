#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE	1
#define FALSE	0

typedef int Data;

typedef struct _node
{
	Data data1;
	Data data2;
	struct _node* next;
} Node;

typedef struct _listStack
{
	Node* head;
} ListStack;

typedef ListStack Stack;	// Useing more general term hiding specification.

void StackInit(Stack* pstack);
int SIsEmpty(Stack* pstack);

void SPush(Stack* pstack, Data data1, Data data2);
void SPop(Stack* pstack, Data* data1, Data* data2);
//Data SPeek(Stack* pstack);

#endif