/*
 * util.h
 *
 *  Created on: Mar 30, 2016
 *      Author: glb
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

int is_grid_full(gridType grid);
int make_move(gridType grid, int column, int PLAYER);
int rand_lim(int limit);
void display_grid(gridType grid);

#endif /* INC_UTIL_H_ */
