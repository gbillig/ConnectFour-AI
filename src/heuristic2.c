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
				if (lineSize == 2) {
					lineCounter[currentPlayer][0]++;
				} else if (lineSize == 3) {
					lineCounter[currentPlayer][1]++;
				}
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
	int currentPlayer, lineSize, numEdges;


	for(j=5; j>=maxHeight; j--) {
		if (connectFour[0] || connectFour[1]) {
			break;
		}

		// currentPlayer possible values:
		// 	P1 - Player 1
		// 	P2 - Player 2
		// 	-1 - Edge of grid
		//  -2 - Empty space

		currentPlayer = -1;
		lineSize = 0;
		numEdges = 1;
		for(i=0; i<7; i++) {
			//when a line ends with an empty space
			if (grid[i][j] == EMPTY) {
				if (lineSize == 2) {
					lineCounter[currentPlayer][0]++;
				} else if (lineSize == 3) {
					lineCounter[currentPlayer][1]++;
				}
				currentPlayer = -2;
				lineSize = 0;
				numEdges = 0;
			}
			// when a line ends but has space to grow on the other side
			else if (currentPlayer != grid[i][j] && numEdges == 0) {
				if (lineSize == 2) {
					lineCounter[currentPlayer][0]++;
				} else if (lineSize == 3) {
					lineCounter[currentPlayer][1]++;
				}
				currentPlayer = grid[i][j];
				lineSize = 1;
				numEdges = 1;
			}
			// when a line continues
			else if (grid[i][j] == currentPlayer) {
				lineSize++;
				if (lineSize == 4) {
					connectFour[currentPlayer] = 1;
					break;
				}
			}
			// when a new line starts
			else if (currentPlayer != grid[i][j]){
				// when an empty space precedes the line, numEdges = 0
				// otherwise it can't grow from that side and numEdges = 1
				numEdges = (currentPlayer == -2) ? 0 : 1;
				lineSize = 1;
				currentPlayer = grid[i][j];
			}
		}
	}
}











