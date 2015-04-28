/*
 * heuristic3.c
 *
 *  Created on: April 27, 2015
 *      Author: gbillig
 */

#include "heuristic3.h"
#include "definitions.h"
#include <stdio.h>
#include <limits.h>

int lineCounter[2][3] = {{0, 0, 0}, {0, 0, 0}};

int heuristic3(gridType grid) {

	int i,j;

	//initialize line counters
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			lineCounter[i][j] = 0;
		}
	}

	int value = 0;
	value += calc_lines3(grid);

	return value;
}

int calc_lines3(gridType grid) {

	int maxHeight;

	searchVertical(grid);
	searchHorizontal(grid);
	searchDiag1(grid);
	searchDiag2(grid);


	int value = 0;

	if (lineCounter[P1][2]) {
		return INT_MAX;
	} else if (lineCounter[P2][2]) {
		return INT_MIN;
	} else {

		int twoLineValue = 3;
		int threeLineValue = 10;

		value += lineCounter[0][0]*twoLineValue + lineCounter[0][1]*threeLineValue;
		value -= lineCounter[1][0]*twoLineValue + lineCounter[1][1]*threeLineValue;
	}

	/*
	printf("%d 2-line found for P1\n", lineCounter[P1][0]);
	printf("%d 3-line found for P1\n", lineCounter[P1][1]);
	printf("%d 4-line found for P1\n", lineCounter[P1][2]);
	printf("%d 2-line found for P2\n", lineCounter[P2][0]);
	printf("%d 3-line found for P2\n", lineCounter[P2][1]);
	printf("%d 4-line found for P2\n", lineCounter[P2][2]);
	*/


	//displayGrid(grid);

	return value;
}

void searchVertical(gridType grid) {

	int top_bound, bottom_bound;
	int i,j;
	//int maxHeight = 0;
	int local_count, local_player, local_valid;

	for (i=0; i<7; i++) {
		bottom_bound = 5;
		top_bound = 2;

		while (top_bound >= 0) {
			local_player = -1;
			local_count = 0;
			local_valid = 1;
			for (j=bottom_bound; j>=top_bound; j--) {
				if (local_valid) {
					if (grid[i][j] != EMPTY) {
						if (local_player == -1) {
							local_player = grid[i][j];
							local_count++;
						} else if (grid[i][j] == local_player) {
							local_count++;
						} else {
							local_valid = 0;
						}
					}
				}
			}

			if (local_valid && local_count > 1) {
				lineCounter[local_player][local_count-2]++;
				/*
				printf("%d-line (vert)  found between (%d,%d) and (%d,%d)\n", local_count,
								i, 5-bottom_bound, i, 5-top_bound);
				*/
			}

			bottom_bound--;
			top_bound--;
		}
	}
}

void searchHorizontal(gridType grid) {
	int left_bound, right_bound;
	int i,j;
	int local_count, local_player, local_valid;

	for (j=0; j<6; j++) {
		left_bound = 0;
		right_bound = 3;

		while (right_bound <= 6) {
			local_player = -1;
			local_count = 0;
			local_valid = 1;
			for (i=left_bound; i<=right_bound; i++) {
				if (local_valid) {
					if (grid[i][j] != EMPTY) {
						if (local_player == -1) {
							local_player = grid[i][j];
							local_count++;
						} else if (grid[i][j] == local_player) {
							local_count++;
						} else {
							local_valid = 0;
						}
					}
				}
			}

			if (local_valid && local_count > 1) {
				lineCounter[local_player][local_count-2]++;
				/*
				printf("%d-line (hor)   found between (%d,%d) and (%d,%d)\n", local_count,
								left_bound, 5-j, right_bound, 5-j);
				*/
			}

			left_bound++;
			right_bound++;

		}
	}
}



void searchDiag1(gridType grid) {
	int top_bound, bottom_bound, left_bound, right_bound;
	int i,j,k;
	int local_count, local_player, local_valid;

	for (k=0; k<6; k++) {

		if (k<2) {
			left_bound = 0;
			right_bound = 3;
			bottom_bound = k + 3;
			top_bound = k;
		} else {
			left_bound = k - 2;
			right_bound = k + 1;
			bottom_bound = 5;
			top_bound = 2;
		}

		while (top_bound >= 0 && right_bound <= 6) {
			local_player = -1;
			local_count = 0;
			local_valid = 1;
			for (i=left_bound, j=bottom_bound; i<=right_bound; i++, j--) {
				if (local_valid) {
					if (grid[i][j] != EMPTY) {
						if (local_player == -1) {
							local_player = grid[i][j];
							local_count++;
						} else if (grid[i][j] == local_player) {
							local_count++;
						} else {
							local_valid = 0;
						}
					}
				}
			}

			if (local_valid && local_count > 1) {
				lineCounter[local_player][local_count-2]++;
				/*
				printf("%d-line (diag1) found between (%d,%d) and (%d,%d)\n", local_count,
								left_bound, 5-bottom_bound, right_bound, 5-top_bound);
				*/
			}

			left_bound++;
			right_bound++;
			top_bound--;
			bottom_bound--;
		}
	}
}

void searchDiag2(gridType grid) {
	int top_bound, bottom_bound, left_bound, right_bound;
	int i,j,k;
	int local_count, local_player, local_valid;

	for (k=0; k<6; k++) {

		if (k<2) {
			right_bound = 6;
			left_bound = 3;
			bottom_bound = k + 3;
			top_bound = k;
		} else {
			right_bound = 8 - k;
			left_bound = 5 - k;
			bottom_bound = 5;
			top_bound = 2;
		}

		while (top_bound >= 0 && left_bound >= 0) {
			local_player = -1;
			local_count = 0;
			local_valid = 1;
			for (i=right_bound, j=bottom_bound; i>=left_bound; i--, j--) {
				if (local_valid) {
					if (grid[i][j] != EMPTY) {
						if (local_player == -1) {
							local_player = grid[i][j];
							local_count++;
						} else if (grid[i][j] == local_player) {
							local_count++;
						} else {
							local_valid = 0;
						}
					}
				}
			}

			if (local_valid && local_count > 1) {
				lineCounter[local_player][local_count-2]++;
				/*
				printf("%d-line (diag2) found between (%d,%d) and (%d,%d)\n", local_count,
								left_bound, 5-top_bound, right_bound, 5-bottom_bound);
				 */
			}

			left_bound--;
			right_bound--;
			top_bound--;
			bottom_bound--;
		}
	}
}
