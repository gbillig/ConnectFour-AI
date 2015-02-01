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

	grid[5][2] = P1;
	grid[5][3] = P1;
	grid[5][4] = P1;


	int h = heuristic(grid_ptr);
	printf("Back in main, reference value: %d\n", grid[2][3]);
	//printf("+Inf: %d\n-Inf: %d\n", P_INF, N_INF);


	return 0;
}
