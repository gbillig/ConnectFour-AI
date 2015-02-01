/*
 * heuristic.h
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

#ifndef HEURISTIC_H_
#define HEURISTIC_H_

#include "definitions.h"

void search(largeGridType grid, int i, int j, int direction, int PLAYER);
int calc_lines(largeGridType grid);
int heuristic(gridType* grid);


int cmpfunc(const void * a, const void * b);

#endif /* HEURISTIC_H_ */
