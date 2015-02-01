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

#define EMPTY	2;
#define P1		0;
#define P2		1;

int main(void) {

	int grid[6][7];
	/*
	 * Grid definitions:
	 * 0 - Player 0
	 * 1 - Player 1
	 * 2 - Empty
	 */
	int i,j;
	for (i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			grid[i][j] = EMPTY;
		}
	}


	int h = heuristic(&grid);
	printf("%d\n", h);


	return 0;
}
