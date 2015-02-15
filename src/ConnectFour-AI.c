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
#include "heuristic.h"
#include "definitions.h"

int endGame(gridType grid);
int minimax(gridType grid, int depth, int maximizingPlayer);
int makeMove(gridType grid, int column, int PLAYER);


int main(void) {

	gridType grid;
	int i,j;
	int fromFile = 0;

	if(fromFile) {
		FILE *fp;
		fp = fopen("/home/gbillig/workspace/ConnectFour-AI/Debug/c4.csv", "r");

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

	time_t start,end;
	double dif;
	int playerMove;
	printf("start\n");
	while (!endGame(grid)) {
		displayGrid(grid);
		time (&start);
		minimax(grid, DEPTH_VALUE, P1);
		time (&end);
		dif = difftime (end,start);
		printf ("Your calculations took %.2lf seconds to run.\n", dif );

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

int minimax(gridType grid, int depth, int maximizingPlayer) {
	int i,j,k;
	if (depth == 0 || endGame(grid)) {
		return heuristic(grid);
	}

	multiGridType childGrid;
	for (k=0; k<7; k++) {
		for (j=0; j<6; j++) {
			for (i=0; i<7; i++) {
				childGrid[k][i][j] = grid[i][j];
			}
		}
	}


	int bestValue, bestMove, value;

	if (maximizingPlayer == P1) {
		bestMove = -1;
		bestValue = INT_MIN;
		for (i=0;i<7; i++) {
			if (makeMove(childGrid[i], i, P1)) {
				value = minimax(childGrid[i], depth - 1, P2);
				if (value > bestValue) {
					bestValue = value;
					bestMove = i;
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
		for (i=0;i<7; i++) {
			if (makeMove(childGrid[i], i, P2)) {
				value = minimax(childGrid[i], depth - 1, P1);
				if (value < bestValue) {
					bestValue = value;
					bestMove = i;
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

int endGame(gridType grid) {
	int i;
	for (i=0;i<7;i++) {
		if (grid[i][0] == EMPTY) {
			return 0;
		}
	}
	return 1;
}
