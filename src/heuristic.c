/*
 * heuristic.c
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

typedef int gridType[6][7];

int heuristic(gridType* grid) {
	int value = 0;

	(*grid)[2][3] = 10;
	printf("%d and %d\n", (*grid)[2][2], (*grid)[2][3]);

	return value;
}
