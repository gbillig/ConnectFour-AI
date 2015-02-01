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
#include "heuristic.h"
#include "definitions.h"

int main(void) {

	gridType grid;
	gridType *grid_ptr = &grid;

	int i,j;
	for (i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			grid[i][j] = EMPTY;
		}
	}

	grid[5][1] = P2;
	grid[5][2] = P1;
	grid[5][3] = P1;
	grid[5][4] = P1;


	int h = heuristic(grid_ptr);

	return 0;
}
