/*
 * util.c
 *
 *  Created on: Mar 30, 2016
 *      Author: glb
 */

#include <limits.h>
#include <stdlib.h>
#include "../inc/definitions.h"

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
					printf(ANSI_COLOR_RED     "1 "     ANSI_COLOR_RESET);
					break;
				case(P2) :
					printf(ANSI_COLOR_GREEN     "2 "     ANSI_COLOR_RESET);
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}
