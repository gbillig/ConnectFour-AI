/*
 * heuristic.c
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

#include "definitions.h"

int twoRow[128][2];
int threeRow[128][3];
int twoRowCounter = 0;
int threeRowCounter = 0;


int heuristic(gridType* gridRef) {
	largeGridType newGrid;
	int i,j;
	for (i=0; i<8; i++) {
		for (j=0; j<9; j++) {
			if (i==0 || i==7 || j==0 || j==8) {
				newGrid[i][j] = EDGE;
			} else {
				newGrid[i][j] = (*gridRef)[i-1][j-1];
			}
		}
	}

	/* Attribute definitions:
	 *
	 * Name: 4 in a line
	 * Value: +INF
	 */

	int value = 0;
	value += calc_diagonals(newGrid);

	newGrid[2][3] = 10;
	printf("Reference value: %d\nLocal Value: %d\n", (*gridRef)[2][3], newGrid[2][3]);

	return value;
}

int calc_diagonals(largeGridType grid) {
	int i,j;
	int PLAYER = P1;
	for (i=1; i<7; i++) {
		for (j=1; j<8; j++) {
			if (grid[i][j] == PLAYER) {
				search(grid, i, j, 0, PLAYER);
				search(grid, i, j, 1, PLAYER);
				search(grid, i, j, 2, PLAYER);
				search(grid, i, j, 3, PLAYER);
			}
		}
	}
	return 0;
}

void search(largeGridType grid, int i, int j, int direction, int PLAYER) {
	int x, y, xOffset, yOffset;
	int diag[4] = {0};
	diag[0] = j + i*8;
	int diagCounter = 1;

	switch(direction) {
		case 0 :
			xOffset = 1;
			yOffset = 0;
			break;
		case 1 :
			xOffset = 0;
			yOffset = 1;
			break;
		case 2 :
			xOffset = 1;
			yOffset = 1;
			break;
		case 3 :
			xOffset =  1;
			yOffset = -1;
			break;
	}

	//search first direction
	int searching = 1;
	int searchCounter = 1;
	while (searching) {
		x = j+xOffset*searchCounter;
		y = i+yOffset*searchCounter;
		if (grid[y][x] == PLAYER) {
			diag[diagCounter] = x + y*8;
			diagCounter++;
			searchCounter++;
		} else {
			searching = 0;
		}
	}

	//search second direction
	searching = 1;
	searchCounter = 1;
	while (searching) {
		x = j+xOffset*searchCounter*(-1);
		y = i+yOffset*searchCounter*(-1);
		if (grid[y][x] == PLAYER) {
			diag[diagCounter] = x + y*8;
			diagCounter++;
			searchCounter++;
		} else {
			searching = 0;
		}
	}

	int emptyDiag = 1;
	int n;
	for (n=0; n<4; n++) {
		if (diag[n] != 0) {
			emptyDiag = 0;
		}
	}
	if (!emptyDiag) {
		printf("Diag found : {%d, %d, %d, %d}\n", diag[0], diag[1], diag[2], diag[3]);
	}
}
