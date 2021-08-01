/* Created on Sunday, August 1, 2021.
Completed on Sunday, August 1, 2021.
Copyright (c) Yonghyeon Cho, Sogang University, Seoul, Korea.
Maze problem using stack concept.
Fundamentals of Data Structures in C, Horowitz et al.
*/

#include <stdio.h>
#include <stdlib.h>
#define false	0
#define TRUE	1

typedef struct {
	short int row, col;
	short int dir;
} element;
typedef struct {
	short int vert, horiz;
} offsets;

char maze[100][100];
char mark[100][100] = { 0, };
int EXIT_ROW, EXIT_COL;
int top;

element stack[10000] = { 0,};
offsets move[8] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };

element Pop();
void Push(element item);

void Path() {
	int row, col, dir = 0, nextRow, nextCol, found = false;
	element position = { 1,1,0 };
	mark[1][1] = 1;
	top = 0;
	stack[0].row = 1, stack[0].col = 1; stack[0].dir = 0;

	while (top > -1 && !found) {
		position = Pop();
		// Turn back along the trace.
		row = position.row;
		col = position.col;
		dir = position.dir;						printf("Popped=> row: %d, col: %d, dir: %d\n", row, col, dir);
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;		//printf("dir: %d\n", dir);
			nextCol = col + move[dir].horiz;	//printf("nextRow: %d, nextCol: %d, maze: %d, mark: %d\n", nextRow, nextCol, maze[nextRow][nextCol]-'0', mark[nextRow][nextCol]);
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = TRUE;
			}
			else if (!(maze[nextRow][nextCol]-'0') && !mark[nextRow][nextCol]) {	// If passable way && not visited.
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;			printf("go! (%d, %d)\n", position.row, position.col);
				Push(position);
				// Follow throught the ongoing way.
				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else
				++dir;
		}
	}

	if (found) printf("Path found\n");
}

int main(void)
{
	int rowNum, colNum;
	FILE* fp = fopen("04-Maze/maze1.txt", "rt");
//	FILE* fp = fopen("04-Maze/maze2.txt", "rt");

	// Scan input file.
	fscanf(fp, "%d %d\n", &rowNum, &colNum);	//printf("%d, %d \n", rowNum, colNum);
	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			fscanf(fp, "%c", &maze[i][j]);		//printf("%c\n", maze[i][j]);
		}
		//printf("*");
		char eol = fgetc(fp);	//printf("%c\n", eol);	// Handle the last character of the line.
		//printf("@\n");
	}

	// Print input file.
	printf("%d %d\n", rowNum, colNum);
	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}

	// Solve a problem with providing the solution.
	EXIT_ROW = 6, EXIT_COL = 4;	// maze1.txt
	//EXIT_ROW = 12, EXIT_COL = 10;	// maze2.txt
	Path();

	// Print contents of the stack.
	printf("===high===\n");
	while (top > -1) {
		printf("%d, %d\n", stack[top].row, stack[top].col);
		top--;
	}
	printf("===low===\n");

	fclose(fp);
	return 0;
}

element Pop()
{
	return stack[top--];
}

void Push(element item)
{
	stack[++top] = item;
}