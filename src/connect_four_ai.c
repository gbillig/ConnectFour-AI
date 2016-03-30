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
#include "../inc/definitions.h"
#include "../inc/util.h"
#include "../inc/heuristic3.h"

int alphabeta(gridType grid, int depth, int alpha, int beta, int maximizingPlayer);

inline int max ( int a, int b ) { return a > b ? a : b; }
inline int min ( int a, int b ) { return a < b ? a : b; }

int main(void) {

	gridType grid;
	int i,j;
	int fromFile = 1;
	srand(time(NULL));

	if(fromFile) {
		FILE *fp;
		fp = fopen("/home/glb/workspace/ConnectFour-AI/board_layout/c4-4.csv", "r");

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

	//displayGrid(grid);
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
					printf("Move %d value: %d\n", i+1, value);
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
