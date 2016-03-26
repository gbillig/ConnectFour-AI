/*
 * heuristic2.c
 *
 *  Created on: Feb 15, 2015
 *      Author: gbillig
 */

#include "../inc/definitions.h"
#include "../inc/heuristic2.h"
#include <limits.h>


int lineCounter[2][2] = {{0, 0}, {0,0}};
int connectFour[2] = {0, 0};
//  lineCounter[PLAYER][lineSize]


int heuristic2(gridType grid) {

	int i,j;

	for (i=0; i<2; i++) {
		connectFour[i] = 0;
		for (j=0; j<2; j++) {
			lineCounter[i][j] = 0;
		}
	}

	int value = 0;
	value += calc_lines2(grid);

	return value;
}


int calc_lines2(gridType grid) {

	int maxHeight;

	maxHeight = searchVertical(grid);
	searchHorizontal(grid, maxHeight);
	searchDiag1(grid);
	searchDiag2(grid);

	int value = 0;

	if (connectFour[0]) {
		return INT_MAX;
	} else if (connectFour[1]) {
		return INT_MIN;
	} else {

		int twoLineValue = 3;
		int threeLineValue = 10;

		value += lineCounter[0][0]*twoLineValue + lineCounter[0][1]*threeLineValue;
		value -= lineCounter[1][0]*twoLineValue + lineCounter[1][1]*threeLineValue;
	}


	printf("%d twoLine found for P1\n", lineCounter[P1][0]);
	printf("%d threeLine found for P1\n", lineCounter[P1][1]);
	printf("%d connectFour found for P1\n", connectFour[P1]);
	printf("%d twoLine found for P2\n", lineCounter[P2][0]);
	printf("%d threeLine found for P2\n", lineCounter[P2][1]);
	printf("%d connectFour found for P2\n", connectFour[P2]);
	printf("maxHeight = %d \n\n", maxHeight);


	//displayGrid(grid);

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
				addLine(lineSize, currentPlayer, 2);
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
	int previousBlock, currentPlayer, lineSize;
	int prevEmptySpaces, postEmptySpaces;


	for(j=5; j>=maxHeight; j--) {
		if (connectFour[0] || connectFour[1]) {
			break;
		}

		// previousBlock possible values:
		// 	P1 - Player 1
		// 	P2 - Player 2
		// 	EDGE - Edge of grid
		//  EMPTY - Empty space

		previousBlock = EDGE;
		lineSize = 0;
		prevEmptySpaces = 0;
		postEmptySpaces = 0;
		for(i=0; i<8; i++) {
			// next block is the edge
			if (i == 7) {
				if (lineSize > 1) {
					addLine(lineSize, currentPlayer, prevEmptySpaces + postEmptySpaces);
				}
			}
			// next block is empty
			else if (grid[i][j] == EMPTY) {
				if (previousBlock == currentPlayer) {
					prevEmptySpaces = postEmptySpaces;
					postEmptySpaces = 0;
				}
				previousBlock = EMPTY;
				postEmptySpaces++;
			}
			// next block is a player
			else if (grid[i][j] == P1 || grid[i][j] == P2) {
				// the line continues
				if (previousBlock == grid[i][j]) {
					lineSize++;
					if (lineSize == 4) {
						connectFour[previousBlock] = 1;
						break;
					}
				}
				// the line is starting
				else if (previousBlock == EMPTY || previousBlock == EDGE) {
					//count previous line
					if (lineSize > 1) {
						addLine(lineSize, currentPlayer, prevEmptySpaces + postEmptySpaces);
					}
					currentPlayer = grid[i][j];
					previousBlock = grid[i][j];
					lineSize = 1;
				}
				// switches from one player to another
				else {
					prevEmptySpaces = postEmptySpaces;
					postEmptySpaces = 0;
					addLine(lineSize, previousBlock, prevEmptySpaces + postEmptySpaces);
					currentPlayer = grid[i][j];
					previousBlock = grid[i][j];
					lineSize = 1;
				}
			}
		}
	}
}

// SW to NE: "/"
void searchDiag1(gridType grid) {
	int i,j,k;
	int previousBlock, currentPlayer, lineSize;
	int prevEmptySpaces, postEmptySpaces;

	for(k=0; k<HOR_SIZE + VER_SIZE; k++) {

		if (k < 6) {
			j = k;
			i = 0;
		} else {
			j = 5;
			i = k - 5;
		}

		if (connectFour[0] || connectFour[1]) {
			break;
		}

		// previousBlock possible values:
		// 	P1 - Player 1
		// 	P2 - Player 2
		// 	EDGE - Edge of grid
		//  EMPTY - Empty space

		previousBlock = EDGE;
		lineSize = 0;
		prevEmptySpaces = 0;
		postEmptySpaces = 0;

		while(j>=-1 && i<=7) {
			// next block is the edge
			if (j == -1 || i == 7) {
				if (lineSize > 1) {
					addLine(lineSize, currentPlayer, prevEmptySpaces + postEmptySpaces);
				}
			}
			// next block is empty
			else if (grid[i][j] == EMPTY) {
				if (previousBlock == currentPlayer) {
					prevEmptySpaces = postEmptySpaces;
					postEmptySpaces = 0;
				}
				previousBlock = EMPTY;
				postEmptySpaces++;
			}
			// next block is a player
			else if (grid[i][j] == P1 || grid[i][j] == P2) {
				// the line continues
				if (previousBlock == grid[i][j]) {
					lineSize++;
					if (lineSize == 4) {
						connectFour[previousBlock] = 1;
						break;
					}
				}
				// the line is starting
				else if (previousBlock == EMPTY || previousBlock == EDGE) {
					//count previous line
					if (lineSize > 1) {
						addLine(lineSize, currentPlayer, prevEmptySpaces + postEmptySpaces);
					}
					currentPlayer = grid[i][j];
					previousBlock = grid[i][j];
					lineSize = 1;
				}
				// switches from one player to another
				else {
					prevEmptySpaces = postEmptySpaces;
					postEmptySpaces = 0;
					addLine(lineSize, previousBlock, prevEmptySpaces + postEmptySpaces);
					currentPlayer = grid[i][j];
					previousBlock = grid[i][j];
					lineSize = 1;
				}
			}

			//iterator
			j--;
			i++;
		}
	}
}

// SE to NW: "\"
void searchDiag2(gridType grid) {
	int i,j,k;
	int previousBlock, currentPlayer, lineSize;
	int prevEmptySpaces, postEmptySpaces;

	for(k=0; k<HOR_SIZE + VER_SIZE; k++) {

		if (k < 6) {
			j = k;
			i = 6;
		} else {
			j = 5;
			i = 6 - (k - 5);
		}

		if (connectFour[0] || connectFour[1]) {
			break;
		}

		// previousBlock possible values:
		// 	P1 - Player 1
		// 	P2 - Player 2
		// 	EDGE - Edge of grid
		//  EMPTY - Empty space

		previousBlock = EDGE;
		lineSize = 0;
		prevEmptySpaces = 0;
		postEmptySpaces = 0;

		while(j>=-1 && i>=-1) {
			// next block is the edge
			if (j == -1 || i == -1) {
				if (lineSize > 1) {
					addLine(lineSize, currentPlayer, prevEmptySpaces + postEmptySpaces);
				}
			}
			// next block is empty
			else if (grid[i][j] == EMPTY) {
				if (previousBlock == currentPlayer) {
					prevEmptySpaces = postEmptySpaces;
					postEmptySpaces = 0;
				}
				previousBlock = EMPTY;
				postEmptySpaces++;
			}
			// next block is a player
			else if (grid[i][j] == P1 || grid[i][j] == P2) {
				// the line continues
				if (previousBlock == grid[i][j]) {
					lineSize++;
					if (lineSize == 4) {
						connectFour[previousBlock] = 1;
						break;
					}
				}
				// the line is starting
				else if (previousBlock == EMPTY || previousBlock == EDGE) {
					//count previous line
					if (lineSize > 1) {
						addLine(lineSize, currentPlayer, prevEmptySpaces + postEmptySpaces);
					}
					currentPlayer = grid[i][j];
					previousBlock = grid[i][j];
					lineSize = 1;
				}
				// switches from one player to another
				else {
					prevEmptySpaces = postEmptySpaces;
					postEmptySpaces = 0;
					addLine(lineSize, previousBlock, prevEmptySpaces + postEmptySpaces);
					currentPlayer = grid[i][j];
					previousBlock = grid[i][j];
					lineSize = 1;
				}
			}

			//iterator
			j--;
			i--;
		}
	}
}

void addLine(int lineSize, int player, int numEmptySpaces) {
	if (player != P1 && player != P2) {
		return;
	}

	if (lineSize == 2 && numEmptySpaces >= 2) {
		lineCounter[player][0]++;
	} else if (lineSize == 3 && numEmptySpaces >= 1) {
		lineCounter[player][1]++;
	}
}










