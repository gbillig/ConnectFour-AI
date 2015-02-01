/*
 * heuristic.c
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

#include "definitions.h"

int heuristic(gridType* gridRef) {
	gridType newGrid;
	int i,j;
	for (i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			newGrid[i][j] = (*gridRef)[i][j];
		}
	}

	/* Attribute definitions:
	 *
	 * Name: 4 in a line
	 * Value: +INFI
	 */

	int value = 0;

	newGrid[2][3] = 10;
	printf("Reference value: %d\nLocal Value: %d\n", (*gridRef)[2][3], newGrid[2][3]);

	return value;
}
