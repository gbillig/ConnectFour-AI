/*
 * definitions.h
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <stdint.h>
/*
 * Grid definitions:
 * 0 - Player 0
 * 1 - Player 1
 * 2 - Empty
 */
#define EMPTY	2;
#define P1		0;
#define P2		1;
#define EDGE	3;
/*
#define P_INF	INT32_MAX;
#define N_INF	INT32_MIN;
*/
typedef int gridType[6][7];
typedef int largeGridType[8][9];




#endif /* DEFINITIONS_H_ */
