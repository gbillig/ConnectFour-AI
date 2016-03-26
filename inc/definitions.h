/*
 * definitions.h
 *
 *  Created on: Feb 1, 2015
 *      Author: gbillig
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <stdint.h>

#define  MAX( a, b ) (( ( a > b) ? a : b ) )
#define  MIN( a, b ) (( ( a < b) ? a : b ) )
//#define MIN(X,Y) ((X) < (Y) ? : (X) : (Y))
//#define MAX(X,Y) ((X) < (Y) ? : (Y) : (X))

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
 * Grid definitions:
 * 0 - Player 0
 * 1 - Player 1
 * 2 - Empty
 * 3 - Edge
 */
#define EMPTY	2
#define P1		0
#define P2		1
#define EDGE	3
#define DEPTH_VALUE 10

#define HOR_SIZE 7
#define VER_SIZE 6

typedef int gridType[7][6];
typedef int largeGridType[9][8];
typedef int multiGridType[7][7][6];




#endif /* DEFINITIONS_H_ */
