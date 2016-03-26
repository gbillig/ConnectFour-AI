/*
 * heuristic.h
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

#ifndef HEURISTIC_H_
#define HEURISTIC_H_

int heuristic(gridType grid);
void search(largeGridType grid, int i, int j, int direction, int PLAYER);
int cmpfunc (const void * a, const void * b);
int array_eq(int *x, int *y, int n);
int calc_lines(largeGridType grid, int PLAYER);


#endif /* HEURISTIC_H_ */
