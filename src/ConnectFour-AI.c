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
#include "heuristic.h"
#include "definitions.h"

int endGame(gridType grid);
int minimax(gridType grid, int depth, int maximizingPlayer);
int makeMove(gridType grid, int column, int PLAYER);


int main(void) {

	gridType grid;
	int i,j;
	int fromFile = 1;

	if(fromFile) {
		FILE *fp;
		fp = fopen("/home/gbillig/workspace/ConnectFour-AI/Debug/c4.csv", "r");

		char buff[255];
		char* inputValue;

		if(fp != NULL) {
			for (i=0;i<6;i++) {
				fgets(buff, 255, (FILE*)fp);
				inputValue = strtok(buff, ",");
				grid[i][0] = atoi(inputValue);
				for (j=1;j<7;j++) {
					inputValue = strtok(NULL, ",");
					grid[i][j] = atoi(inputValue);
				}
			}
		}
		fclose(fp);
	} else {
		for (i=0; i<6; i++) {
			for (j=0; j<7; j++) {
				grid[i][j] = EMPTY;
			}
		}
	}

	int playerMove;
	while (!endGame(grid)) {
		minimax(grid, DEPTH_VALUE, 1);
		printf("Player 1's turn. Column? ");
		scanf("%d", &playerMove);
		printf("\n");
		makeMove(grid, playerMove, P1);

		printf("Player 2's turn. Column? ");
		scanf("%d", &playerMove);
		printf("\n");
		makeMove(grid, playerMove, P2);
	}


	int h = heuristic(grid);
	printf("h = %d\n", h);

	return 0;
}

int minimax(gridType grid, int depth, int maximizingPlayer) {
	int i,j,k;
	if (depth == 0 || endGame(grid)) {
		return heuristic(grid);
	}

	gridType childGrid[7];
	for (k=0; k<7; k++) {
		for (i=0; i<6; i++) {
			for (j=0; j<7; j++) {
				childGrid[k][i][j] = grid[i][j];
			}
		}
	}


	int bestValue;
	int bestMove = 3;
	int value;
	if (maximizingPlayer) {
		bestValue = 0;
		for (i=0;i<7; i++) {
			if (makeMove(childGrid[i], i, P1)) {
				value = minimax(childGrid[i], depth - 1, 0);
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
	} else {
		bestValue = INT_MAX;
		for (i=0;i<7; i++) {
			if (makeMove(childGrid[i], i, P2)) {
				value = minimax(childGrid[i], depth - 1, 1);
				if (value < bestValue) {
					bestValue = value;
					bestMove = i;
				}
			}
		}
		return bestValue;
	}
}

int makeMove(gridType grid, int column, int PLAYER) {
	if (grid[0][column] != EMPTY) {
		return 0;
	}
	int i;
	for (i=5; i>=0; i--) {
		if (grid[i][column] == EMPTY) {
			grid[i][column] = PLAYER;
			return 1;
		}
	}

	return 1;
}

int endGame(gridType grid) {
	int i;
	for (i=0;i<7;i++) {
		if (grid[0][i] == EMPTY) {
			return 0;
		}
	}
	return 1;
}
