/* Created on Tuesday, July 27, 2021.
Completed on Wednesday, July 28, 2021.
Copyright (c) Yonghyeon Cho, Sogang University, Seoul, Korea.
Biconnected Components.
Fundamentals of Data Structures in C, Horowitz et al.
*/

#include "ListBaseStack.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES	30
#define MIN2(x,y)		((x) < (y) ? (x) : (y))
#define FALSE			0

short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;	// for incremental use when executing bicon algorithm.
int n;		// # of vertices.

short int* visited;

typedef struct node {
	int vertex;
	struct node* link;
} node;
typedef struct node* nodePointer;
nodePointer* graph;		// adjacent list headers.

void init();
void dfnlow(int, int);

Stack stack;			// defining a stack.
void bicon(int, int);

int main(void)
{
	// storing the given graph //
//	FILE* fp = fopen("10-Biconnected_components/input1.txt", "rt");
	FILE* fp = fopen("10-Biconnected_components/input2.txt", "rt");
	fscanf(fp, "%d", &n);					//printf("input num: %d\n", n);
	graph = (nodePointer*)malloc(n * sizeof(nodePointer));	//printf("%d\n", sizeof(adjLists));
	for (int i = 0; i < n; i++)
	{
		int v_num;
		char c = '\0';
		fscanf(fp, "%d", &v_num);			//printf("v_num: %d\n", v_num);
		
		nodePointer prev = NULL;
		while (c != '\n') {
			c = fgetc(fp);
			if (c == EOF) break;
			if (c != ' ' && c != '\n') {
				int input = c - '0';		//printf("%d: %d \n", i, input);
				nodePointer temp = (nodePointer)malloc(1 * sizeof(node));
				temp->vertex = input;
				temp->link = NULL;
				if (prev == NULL) {
					graph[v_num] = temp;
					prev = temp;
				}
				else {
					prev->link = temp;
					prev = temp;
				}							//printf("%d ", temp->data);
			}
		}									//printf("\n");
	}

	// spare check flags which represent whether a node was visited or not //
	visited = (short int*)malloc(n * sizeof(short int));
	
	// printing the stored adjacent list //
	for (int i = 0; i < n; i++)
	{
		nodePointer cur = NULL;
		printf("%d: ", i);
		for (cur = graph[i]; cur != NULL; cur = cur->link) {
			printf("%d ", cur->vertex);
		}
		printf("\n");
	}

	// executing dfnlow process //
	init();						printf("\n");
	dfnlow(3, -1);
	for (int i = 0; i < n; i++) printf("%d %d %d\n", visited[i], dfn[i], low[i]);

	// initializing a Stack //
	StackInit(&stack);

	// executing bicon process //
	init();						printf("\n");
	bicon(3, -1);				printf("\n");
//	for (int i = 0; i < n; i++) printf("%d %d %d\n", visited[i], dfn[i], low[i]);

	return 0;
}

void init()
{
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;	
//	for (i = 0; i < n; i++)	printf("%d %d %d\n", visited[i], dfn[i], low[i]);
}

void bicon(int u, int v)
{
	/* compute dfn and low, and output the edges of G by their
	biconnected components, v is the parent of (if any) u
	in the resulting spanning tree. It is assumed that all
	entries of dfn[] have been initialized to -1, num is
	initially to 0, and the stack is initially empty */

	nodePointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;			//printf("%d \n", w);
		if (v != w && dfn[w] < dfn[u]) {	// not a parent && 
			SPush(&stack, u, w);	printf("%d < %d	(%d %d)\n", dfn[w], dfn[u], u, w);	/* add edge to stack */
		}
		if (dfn[w] < 0) {
			bicon(w, u);
			low[u] = MIN2(low[u], low[w]);
			if (low[w] >= dfn[u]) {		// the very case of biconnected component.
				printf("New biconnected component: ");
				do {										/* deleting edge from stack */
					SPop(&stack, &x, &y);
					printf(" <%d, %d>", x, y);
				} while (!((x == u) && (y == w)));
				printf("\n");
			}
		}
		else if (w != v) low[u] = MIN2(low[u], dfn[w]);		// handling back edges.
	}
}

void dfnlow(int u, int v)
{
	/* compute dfn and low while performing a dfs search
	beginning at vertedx u, v is the parent of u (if any) */

	nodePointer ptr;
	int w;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;			//printf("%d \n", w);
		if (dfn[w] < 0) {
			dfnlow(w, u);
			low[u] = MIN2(low[u], low[w]);
		}
		else if (w != v)
			low[u] = MIN2(low[u], dfn[w]);
	}
}