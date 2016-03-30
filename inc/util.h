/*
 * util.h
 *
 *  Created on: Mar 30, 2016
 *      Author: glb
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

int gridFull(gridType grid);
int makeMove(gridType grid, int column, int PLAYER);
int rand_lim(int limit);
void displayGrid(gridType grid);

#endif /* INC_UTIL_H_ */
