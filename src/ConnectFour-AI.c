/*
 ============================================================================
 Name        : ConnectFour-AI.c
 Author      : Gleb Billig
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
//#include "heuristic.h"
//#include "heuristic2.h"
#include "heuristic3.h"
#include "definitions.h"

int gridFull(gridType grid);
int alphabeta(gridType grid, int depth, int alpha, int beta, int maximizingPlayer);
int makeMove(gridType grid, int column, int PLAYER);
int rand_lim(int limit);
void displayGrid(gridType grid);

inline int max ( int a, int b ) { return a > b ? a : b; }
inline int min ( int a, int b ) { return a < b ? a : b; }

int main(void) {

	gridType grid;
	int i,j,k;
	int fromFile = 1;
	srand(time(NULL));

	if(fromFile) {
		FILE *fp;
		fp = fopen("/home/gbillig/workspace/ConnectFour-AI/Debug/c4-3.csv", "r");

		char buff[255];
		char* inputValue;

		if(fp != NULL) {
			for (j=0; j<6; j++) {
				fgets(buff, 255, (FILE*)fp);
				inputValue = strtok(buff, ",");
				grid[0][j] = atoi(inputValue);
				for (i=1; i<7; i++) {
					inputValue = strtok(NULL, ",");
					grid[i][j] = atoi(inputValue);
				}
			}
		}
		fclose(fp);
	} else {
		for (j=0; j<6; j++) {
			for (i=0; i<7; i++) {
				grid[i][j] = EMPTY;
			}
		}
	}

	//heuristic3(grid);


	int playerMove;
	printf("start\n");
	while (!gridFull(grid)) {
		displayGrid(grid);
		alphabeta(grid, DEPTH_VALUE, INT_MIN, INT_MAX, P1);

		printf("Player 1's turn. Column? ");
		scanf("%d", &playerMove);
		printf("\n");
		makeMove(grid, playerMove-1, P1);

		displayGrid(grid);
		printf("Player 2's turn. Column? ");
		scanf("%d", &playerMove);
		printf("\n");
		makeMove(grid, playerMove-1, P2);
	}


	/*
	int k;
	multiGridType childGrid;
	for (k=0; k<7; k++) {
		for (j=0; j<6; j++) {
			for (i=0; i<7; i++) {
				childGrid[k][i][j] = grid[i][j];
			}
		}
	}

	int h;
	for (i=0; i<7; i++) {
		makeMove(childGrid[i], i, P1);
		h = heuristic(grid);
		printf("For move %d, h = %d\n", i, h);
	}
	*/

	return 0;
}

int alphabeta(gridType grid, int depth, int alpha, int beta, int maximizingPlayer) {
	int i,j,k;

	if (depth == 0 || gridFull(grid)) {
		return heuristic3(grid);
	}

	multiGridType childGrid;
	for (k=0; k<7; k++) {
		for (j=0; j<6; j++) {
			for (i=0; i<7; i++) {
				childGrid[k][i][j] = grid[i][j];
			}
		}
	}


	int bestMove, value, bestValue;

	if (maximizingPlayer == P1) {
		bestMove = -1;
		bestValue = INT_MIN;
		for (i=0; i<7; i++) {
			if (makeMove(childGrid[i], i, P1)) {
				value = alphabeta(childGrid[i], depth - 1, alpha, beta, P2);
				if (value > bestValue) {
					bestValue = value;
					bestMove = i;
				}

				alpha = max(bestValue, alpha);
				if (beta <= alpha) {
					break;
				}
				if (depth == DEPTH_VALUE) {
					printf("Move %d value: %d\n", i, value);
				}

			}
		}
		if (depth == DEPTH_VALUE) {
			printf("AI recommends column %d.\n", bestMove+1);
		}
		return bestValue;

	} else if (maximizingPlayer == P2) {
		bestMove = -1;
		bestValue = INT_MAX;
		for (i=0; i<7; i++) {
			if (makeMove(childGrid[i], i, P2)) {
				value = alphabeta(childGrid[i], depth - 1, alpha, beta, P1);
				if (value < bestValue) {
					bestValue = value;
					bestMove = i;
				}

				beta  = min(value, beta);
				if (beta <= alpha) {
					break;
				}
			}
		}
		return bestValue;
	}

	return -1;
}

int makeMove(gridType grid, int column, int PLAYER) {
	if (grid[column][0] != EMPTY) {
		return 0;
	}
	int i;
	for (i=5; i>=0; i--) {
		if (grid[column][i] == EMPTY) {
			grid[column][i] = PLAYER;
			return 1;
		}
	}

	return 1;
}

int gridFull(gridType grid) {
	int i;
	for (i=0;i<7;i++) {
		if (grid[i][0] == EMPTY) {
			return 0;
		}
	}
	return 1;
}

int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do {
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

void displayGrid(gridType grid) {
	int i,j;
	for (j=0; j<6; j++) {
		for (i=0; i<7; i++) {
			switch(grid[i][j]) {
				case(EMPTY) :
					printf("* ");
					break;
				case(P1) :
					printf("1 ");
					break;
				case(P2) :
					printf("2 ");
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}
