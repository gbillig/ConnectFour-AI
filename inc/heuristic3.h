/*
 * heuristic3.h
 *
 *  Created on: Feb 15, 2015
 *      Author: gbillig
 */

#ifndef HEURISTIC3_H_
#define HEURISTIC3_H_

int heuristic3(gridType grid);
int calc_lines3(gridType grid);

void searchVertical(gridType grid);
void searchHorizontal(gridType grid);
void searchDiag1(gridType grid);
void searchDiag2(gridType grid);


#endif /* HEURISTIC3_H_ */
