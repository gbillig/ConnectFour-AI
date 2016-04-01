/*
 * util.c
 *
 *  Created on: Mar 30, 2016
 *      Author: glb
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/definitions.h"

int isEndgame(gridType grid, int column, int row, int PLAYER) {
	int top_bound, right_bound, bottom_bound, left_bound;
	int i,j;
	int line_length;

	top_bound =  MAX(row - 3, 0);
	bottom_bound = MIN(row + 3, 5);
	left_bound = MAX(column - 3, 0);
	right_bound = MIN(column + 3, 6);

	// vertical
	line_length = 1;
	for (j = row - 1; j >= top_bound; j--) {
		if (grid[column][j] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	for (j = row + 1; j <= bottom_bound; j++) {
		if (grid[column][j] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	if (line_length >= 4) {
		return 1;
	}

	//horizontal
	line_length = 1;
	for (i = column - 1; i >= left_bound; i--) {
		if (grid[i][row] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	for (i = column + 1; i <= right_bound; i++) {
		if (grid[i][row] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	if (line_length >= 4) {
		return 1;
	}

	//diag_/
	line_length = 1;
	for (i = column - 1, j = row + 1; i >= left_bound && j <= bottom_bound; i--, j++) {
		if (grid[i][j] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	for (i = column + 1, j = row - 1; i <= right_bound && j >= top_bound; i++, j--) {
		if (grid[i][j] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	if (line_length >= 4) {
		return 1;
	}

	//diag_\
    line_length = 1;
	for (i = column - 1, j = row - 1; i >= left_bound && j >= top_bound; i--, j--) {
		if (grid[i][j] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	for (i = column + 1, j = row + 1; i <= right_bound && j <= bottom_bound; i++, j++) {
		if (grid[i][j] == PLAYER) {
			line_length++;
		} else {
			break;
		}
	}
	if (line_length >= 4) {
		return 1;
	}

	return 0;
}

int makeMove(gridType grid, int column, int PLAYER) {
	if (grid[column][0] != EMPTY) {
		return 0;
	}
	int i;
	for (i=5; i>=0; i--) {
		if (grid[column][i] == EMPTY) {
			grid[column][i] = PLAYER;
			if (isEndgame(grid, column, i, PLAYER)) {
				return 2;
			}
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
