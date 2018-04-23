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
#include <limits.h>
#include <string.h>
#include <time.h>
#include "../inc/definitions.h"
#include "../inc/util.h"
#include "../inc/heuristic3.h"

int alphabeta(gridType grid, int depth, int alpha, int beta, int maximizingPlayer, int absolute_depth);

int main(int argc, char** argv) {

	if (argc == 2 && strcmp(argv[1], "-nocolor") == 0) {
		print_mode = 0;
	} else {
		print_mode = 1;
	}

	gridType grid;
	int i,j;
	int fromFile = 1;
	srand(time(NULL));

	if (fromFile) {
		FILE *fp;
		fp = fopen("/home/glb/workspace/connect-four-ai/board_layout/c4-4.csv", "r");

		char buff[255];
		char* inputValue;

		if (fp != NULL) {
			for (j = 0; j < 6; j++) {
				fgets(buff, 255, (FILE*)fp);
				inputValue = strtok(buff, ",");
				grid[0][j] = atoi(inputValue);
				for (i = 1; i < 7; i++) {
					inputValue = strtok(NULL, ",");
					grid[i][j] = atoi(inputValue);
				}
			}
		}
		fclose(fp);
	} else {
		for (j = 0; j < 6; j++) {
			for (i = 0; i < 7; i++) {
				grid[i][j] = EMPTY;
			}
		}
	}

	//printf("%d\n", make_move(grid, 4, P1));

	//display_grid(grid);
	//heuristic3(grid);

	//printf("makeMove returns %d\n", makeMove(grid, 1, P1));
	//alphabeta(grid, 2, INT_MIN, INT_MAX, P1, 2);

	int playerMove, depth, move_count, move_result;
	depth = DEPTH_VALUE;
	move_count = 1;


	printf("start\n");
	while (!is_grid_full(grid)) {
		if (move_count % 6 == 0) {
			depth += 2;
		}

		display_grid(grid);
		alphabeta(grid, depth, INT_MIN, INT_MAX, P1, depth);

		printf("Player 1's turn. Column? ");
		scanf("%d", &playerMove);
		printf("\n");
		move_result = make_move(grid, playerMove - 1, P1);
		if (move_result == 2) {
			display_grid(grid);
			printf("AI WINS!\n");
			break;
		}

		display_grid(grid);
		printf("Player 2's turn. Column? ");
		scanf("%d", &playerMove);
		printf("\n");
		move_result = make_move(grid, playerMove - 1, P2);
		if (move_result == 2) {
			display_grid(grid);
			printf("CONGRATULATIONS, YOU WON!\n");
			break;
		}

		move_count++;
	}



	/*
	int k;
	multiGridType childGrid;
	for (k=0; k<7; k++) {
		for (j=0; j<6; j++) {
			for (i=0; i<7; i++) {
				childGrid[k][i][j] = grid[i][j];
			}
		}
	}

	int h;
	for (i=0; i<7; i++) {
		makeMove(childGrid[i], i, P1);
		h = heuristic(grid);
		printf("For move %d, h = %d\n", i, h);
	}
	*/

	return 0;
}

int alphabeta(gridType grid, int depth, int alpha, int beta, int maximizingPlayer, int absolute_depth) {
	int i,j,k;
	int bestMove, value, bestValue, moveResult;

	if (depth == 0 || is_grid_full(grid)) {
		value = heuristic3(grid);
		//displayGrid(grid);
		//printf("Heuristic value: %d\n", value);
		return value;
	}

	multiGridType childGrid;
	for (k = 0; k < 7; k++) {
		for (j = 0; j < 6; j++) {
			for (i = 0; i < 7; i++) {
				childGrid[k][i][j] = grid[i][j];
			}
		}
	}

	if (maximizingPlayer == P1) {
		bestMove = -1;
		bestValue = INT_MIN;
		for (i = 0; i < 7; i++) {
			moveResult = make_move(childGrid[i], i, P1);

			if (moveResult == 1) {
				// continue alphabeta execution
				value = alphabeta(childGrid[i], depth - 1, alpha, beta, P2, absolute_depth);
				if (value > bestValue) {
					bestValue = value;
					bestMove = i;
				}

				alpha = MAX(bestValue, alpha);

				//printf("Maximizing P1. V = %d\n", value);
				//display_grid(grid);

				// prune
				if (beta <= alpha) {
					break;
				}

				/*
				if (depth == absolute_depth) {
					printf("Move %d value: %d\n", i+1, value);
				}
				*/


			} else if (moveResult == 2){
				// reached endgame scenario
				bestMove = i;
				bestValue = INT_MAX - (DEPTH_VALUE - depth) * 10;
				break;
			}
		}
		if (depth == absolute_depth) {

			if (bestMove == -1) {
				printf("AI concedes. YOU WIN!\n");
			} else {
				printf("AI recommends column %d.\n", bestMove+1);
			}
		}
		return bestValue;

	} else if (maximizingPlayer == P2) {
		bestMove = -1;
		bestValue = INT_MAX;
		for (i = 0; i < 7; i++) {
			moveResult = make_move(childGrid[i], i, P2);

			if (moveResult == 1) {
				// continue alphabeta execution
				value = alphabeta(childGrid[i], depth - 1, alpha, beta, P1, absolute_depth);
				if (value < bestValue) {
					bestValue = value;
					bestMove = i;
				}

				beta = MIN(value, beta);

				//printf("Maximizing P2. V = %d\n", value);
				//display_grid(grid);

				// prune
				if (beta <= alpha) {
					break;
				}

			} else if (moveResult == 2) {
				// reached endgame scenario
				bestMove = i;
				bestValue = INT_MIN + (DEPTH_VALUE - depth) * 10;
				break;
			}
		}
		return bestValue;
	}

	return -1;
}
