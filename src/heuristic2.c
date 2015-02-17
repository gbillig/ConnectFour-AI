/*
 * heuristic2.c
 *
 *  Created on: Feb 15, 2015
 *      Author: gbillig
 */

#include "heuristic2.h"
#include "definitions.h"
#include <limits.h>


int lineCounter[2][2] = {0};
int connectFour[2] = {0, 0};
//  lineCounter[PLAYER][lineSize]


int heuristic2(gridType grid) {

	int value = 0;
	value += calc_lines2(grid);

	return value;
}


int calc_lines2(gridType grid) {
	int i,j;
	int maxHeight;

	//maxHeight = searchVertical(grid);
	maxHeight = 0;
	searchHorizontal(grid, maxHeight);

	int value = 0;

	/*
	if (connectFour) {
		return INT_MAX;
	} else {
		int twoLineValue = 3;
		int threeLineValue = 10;
		value = twoLineCounter[PLAYER]*twoLineValue + threeLineCounter[PLAYER]*threeLineValue;
	}
	*/

	printf("%d twoLine found for P1\n", lineCounter[P1][0]);
	printf("%d twoLine found for P2\n", lineCounter[P2][0]);
	printf("%d threeLine found for P1\n", lineCounter[P1][1]);
	printf("%d threeLine found for P2\n", lineCounter[P2][1]);
	printf("%d connectFour found for P1\n", connectFour[P1]);
	printf("%d connectFour found for P2\n", connectFour[P2]);
	printf("maxHeight = %d \n\n", maxHeight);

	return value;
}

int searchVertical(gridType grid) {
	int i,j;
	int currentPlayer, lineSize, maxHeight;
	maxHeight = 5;

	for(i=0; i<7; i++) {

		if (connectFour[0] || connectFour[1]) {
			break;
		}

		currentPlayer = -1;
		lineSize = 0;
		for(j=5; j>=0; j--) {
			// when a line ends with an empty space
			if (grid[i][j] == EMPTY) {
				addLine(lineSize, currentPlayer);
				//break because nothing can be above
				break;
			}
			// when a line continues
			else if (grid[i][j] == currentPlayer) {
				lineSize++;
				if (lineSize == 4) {
					connectFour[currentPlayer] = 1;
					break;
				}
			}
			// when a line ends and is blocked on both sides
			else if (currentPlayer != grid[i][j]){
				currentPlayer = grid[i][j];
				lineSize = 1;
			}

			maxHeight = (j < maxHeight) ? j : maxHeight;
		}
	}

	return maxHeight;
}


void searchHorizontal(gridType grid, int maxHeight) {
	int i,j;
	int currentPlayer, lineSize, numEmptySpaces;


	for(j=5; j>=maxHeight; j--) {
		if (connectFour[0] || connectFour[1]) {
			break;
		}

		// currentPlayer possible values:
		// 	P1 - Player 1
		// 	P2 - Player 2
		// 	EDGE - Edge of grid
		//  EMPTY - Empty space

		currentPlayer = EDGE;
		lineSize = 0;
		numEmptySpaces = 0;
		for(i=0; i<8; i++) {
			// next block is the edge
			if (i == 7) {
				if (numEmptySpaces > 0) {
					addLine(lineSize, currentPlayer);
				}
			}
			// next block is empty
			else if (grid[i][j] == EMPTY) {
				// the line has ended
				if (currentPlayer == P1 || currentPlayer == P2) {
					addLine(lineSize, currentPlayer);
				}

				currentPlayer = EMPTY;
				lineSize = 0;
				numEmptySpaces++;
			}
			// next block is a player
			else if (grid[i][j] == P1 || grid[i][j] == P2) {
				// the line continues
				if (currentPlayer == grid[i][j]) {
					lineSize++;
					if (lineSize == 4) {
						connectFour[currentPlayer] = 1;
						break;
					}
				}
				// the line is starting
				else if (currentPlayer == EMPTY || currentPlayer == EDGE) {
					currentPlayer = grid[i][j];
					lineSize = 1;
				}
				// switches from one player to another
				else {
					addLine(lineSize, currentPlayer);
					currentPlayer = grid[i][j];
					lineSize = 1;
					numEmptySpaces = 0;
				}
			}
		}
	}
}

void addLine(int lineSize, int currentPlayer) {
	if (currentPlayer != P1 && currentPlayer != P2) {
		return;
	}

	if (lineSize == 2) {
		lineCounter[currentPlayer][0]++;
	} else if (lineSize == 3) {
		lineCounter[currentPlayer][1]++;
	}
}










